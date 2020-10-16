# Info Corona

Sebuah Program Utility Ringan untuk menampilkan informasi terkini tentang Covid-19

### Cara menjalankan (Versi PHP)
```sh
php corona.php
```

### Cara Compile (Versi C)
#### Kebutuhan
- clang
- libcurl
- json-c (dapatkan di https://github.com/json-c/json-c)

```sh
clang -Wall -g -I/usr/local/include/json-c -I/usr/include/x86_64-linux-gnu/curl -o corona corona.c -ljson-c -lcurl
```



### Cara menjalankan (Versi Python3)
#### Kebutuhan
- python3
- pip requests
```sh
python3 corona.py
```



### Cara menjalankan (Versi Javascript)
#### requirment
- browser
- open your index.html on browser
