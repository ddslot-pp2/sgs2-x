#include <iostream>
#include "server/server.h"
#include "io_helper.h"
#include "server_session/server_session.h"
#include "packet_processor/packet_processor.h"
#include <csignal>
#include <boost/variant.hpp>
#include <queue>
#include <type_traits>   

std::mutex m;
std::condition_variable cv;
std::atomic_bool stop = false;

void sig_handler(int signal_val)
{
    //std::sig_atomic_t v = signal_val;
    stop = true;
    cv.notify_all();
}

class component
{
public:
    virtual ~component() {}
};

class move_component : public component
{
public:
    void say_hello(std::string msg)
    {
        std::cout << msg << std::endl;
    }
};

class skill_component : public component
{
public:
    void attack(int id, std::string msg)
    {

    }
};

struct msg
{
    std::shared_ptr<component> comp;
    std::shared_ptr<std::function<void()>> callback;
};


class object
{
public:
    virtual ~object() {}

    void update()
    {
        while (!q_.empty())
        {
            auto& f = q_.front();
            f();
            //m.event(m.comp);

            q_.pop();
        }
    }

    void hello(int a)
    {
        std::cout << a << std::endl;
    }

    std::vector<std::shared_ptr<component>> comps_;
    std::queue<std::function<void()>> q_;
};

class player : public object
{
public:

    void say_hp(float hp)
    {
        std::cout << hp << std::endl;
    }

    int hp_;
};

template <class T, class Tuple>
struct Index;

template <class T, class... Types>
struct Index<T, std::tuple<T, Types...>> {
    static const std::size_t value = 0;
};

template <class T, class U, class... Types>
struct Index<T, std::tuple<U, Types...>> {
    static const std::size_t value = 1 + Index<T, std::tuple<Types...>>::value;
};

typedef std::tuple<move_component, skill_component> comp_t;

template <typename C, typename Fn, typename... Args>
void push_component_task(std::shared_ptr<object> obj, Fn f, Args&&... args)
{
    std::cout << Index<C, comp_t>::value << std::endl;

    constexpr auto index = Index<C, comp_t>::value;

    auto comp = std::static_pointer_cast<C>(obj->comps_[index]);
    auto callback = std::bind(f, comp, std::forward<Args>(args)...);
    obj->q_.push(callback);
}

template <typename Fn, typename... Args>
void push_object_task(std::shared_ptr<object> obj, Fn f, Args&&... args)
{
    auto callback = std::bind(f, obj, std::forward<Args>(args)...);
    obj->q_.push(callback);
}

template <typename P, typename Fn, typename... Args>
void push_player_task(std::shared_ptr<object> obj, Fn f, Args&&... args)
{
    static_assert(std::is_base_of<object, P>::value, "is not base of object");

    auto callback = std::bind(f, std::static_pointer_cast<P>(obj), std::forward<Args>(args)...);
    obj->q_.push(callback);
}


void test()
{

    std::shared_ptr<object> obj = std::make_shared<player>();
    obj->comps_ = {
        std::make_shared<move_component>(),
        std::make_shared<skill_component>()
    };

    push_component_task<move_component>(obj, &move_component::say_hello, "aaa");
    push_object_task(obj, &object::hello, 10);
    push_player_task<player>(obj, &player::say_hp, 20.2f);

    obj->update();

    //obj->q_.push(f);
}

int main()
{
    test();

    getchar();
    return 0;

    // 서버 종료 ctrl + break
    std::signal(SIGBREAK, sig_handler);

    // 로케일 설정
    std::locale::global(std::locale(""));
    std::wcout.imbue(std::locale(""));

    // 패킷 등록
    register_handlers();
    network::initialize();

    // 서버 생성
    tcp::endpoint endpoint(tcp::v4(), 3000);
    auto svr = std::make_unique<network::server<server_session>>(network::io_service(), endpoint);

    const auto num_cpus = std::thread::hardware_concurrency();
    network::start(num_cpus);

    std::unique_lock<std::mutex> lk(m);

    cv.wait(lk, []
    {
        if (stop)
        {
            wprintf(L"서버 종료 알림\n");
            return true;
        }

        wprintf(L"메인 스레드 대기\n");
        return false;
    });

    wprintf(L"서버 종료 시작\n");
    network::stop();

    return 0;
}
