## Prerequisites
Upload `fastcgi_example_1_0_0_armv7hf.eap` and `vdoencodeclient_1_0_0_armv7hf.eap` to Axis device.

Run `fastcgi_example_1_0_0_armv7hf` on Axis device

Set `IP address`, `user` and `password` in `config/configs.xml` file.

Run http server
```
python2 http_server/http-server.py 8080
```

## Build application
```
cmake -B build
cmake --build build
```

## Run application
Do not forget to set `IP address`, `user` and `password` in `config/configs.xml` file

```
build/AxisDataRetriever config/configs.xml
```
