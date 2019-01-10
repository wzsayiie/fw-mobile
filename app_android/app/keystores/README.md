There is *master.jks*,
it's default signature file for flavor *master*,
referenced by *app/build.gradle*,
and makes *build_android.sh* work properly.

It only contains one key:

    file name    : master.jks
    file password: master
    key alias    : master
    key password : master

Developer can replace *master.jks*,
or add new keystore files for other flavors here.
