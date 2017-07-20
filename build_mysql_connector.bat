cd mysql-connector-c-6.1.10
cmake -G "Visual Studio 14 2015 Win64" -DWINDOWS_RUNTIME_MD=1

"C:\Program Files (x86)\MSBuild\14.0\Bin\MSBuild.exe" "./LibMySQL.sln" /p:Configuration=Debug /p:Platform=x64 /t:rebuild
"C:\Program Files (x86)\MSBuild\14.0\Bin\MSBuild.exe" "./LibMySQL.sln" /p:Configuration=Release /p:Platform=x64 /t:rebuild

cd..

cd mysql-connector-c++-1.1.9
cmake -G "Visual Studio 14 2015 Win64" -DMYSQLCLIENT_STATIC_LINKING=1 -DCMAKE_ENABLE_C++11=1 -DBOOST_ROOT="../boost".

"C:\Program Files (x86)\MSBuild\14.0\Bin\MSBuild.exe" "./MYSQLCPPCONN.sln" /p:Configuration=Debug /p:Platform=x64 /t:rebuild
"C:\Program Files (x86)\MSBuild\14.0\Bin\MSBuild.exe" "./MYSQLCPPCONN.sln" /p:Configuration=Release /p:Platform=x64 /t:rebuild
