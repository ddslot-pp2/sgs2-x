[설명]

protobuf3 를 활용 유니티와 간단한 tcp 통신

기본 셋팅은 vs2015 

다른 버젼이 필요하다면 protobuf_soultion.py와 build_protobuf.bat에서 버젼 설정필요


[설치]

1. build_boost.bat 실행해서 boost 설치

2. protobuf_solution.py 실행해서 protobuf3 vs2015 솔루션 파일 생성

3. build_protobuf.bat 실행해서 protobuf3 관련 라이브러리 생성

4. data/protobuf/create_protobuf.py 실행해서 data/protobuf/packet.xml에 정의된 xml형식 패킷을 proto로 자동생성 및 관련 파일 생성

