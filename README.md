예제 코드 컴파일
==============

이 파일의 내용은 부록에 있는 예제코드를 어떻게 컴파일 할 수 있는지 설명하도록 한다. 보다 자세한 내용은 서적의 부록 내용을 참고하길 바란다.

<!-- TOC Start -->
## 차례

* [환경 구축](#환경-구축)
  * [리눅스](#리눅스)
  * [윈도우](#윈도우)
* [설정 변경](#설정-변경)
* [컴파일](#컴파일)

<!-- TOC End -->

## 환경 구축
환경은 크게 윈도우와 리눅스(Ubuntu)로 구분하여 설명하도록 한다.

### 리눅스

리눅스(Ubuntu)의 경우 아래의 명령어로 관련 패키지를 설치하면 된다.

> $ sudo apt-get install build-essential python scons libpcap-dev

### 윈도우

> - VisualStudio - https://www.visualstudio.com/downloads/
> - Python - https://www.python.org/downloads/
> - Scons - https://www.scons.org/

위의 프로그램을 설치한 뒤에 Winpcap Driver를 다운로드 받아 설치하고 Winpcap Developer's Pack을 다운로드 받은 뒤에 압축을 해제 하면 된다. 

먼저 Winpcap Driver는 아래의 링크에서 다운 받을 수 있으며, 다운 받은 파일이 실행 파일이기 때문에 다운로드 받은 실행 파일을 실행하여 Driver를 설치하면 된다.


> http://www.winpcap.org/install/default.htm

Winpcap Developer's Pack은 Winpcap 라이브러리를 이용하여 프로그램을 개발하는데 필요한 파일들을 모두 둔 것으로 이 파일 안에는 헤더 파일과 라이브러 파일, 그리고 예제 파일등이 포함되어 있다. 아래의 링크에서 Developer's Pack 파일을 다운로드 받은 뒤에 압축 파일을 해제 한다. 

> http://www.winpcap.org/devel.htm

이로서 개발 환경 준비는 완료되었고, 압축 해제한 Developer's Pack 파일의 경로는 예제 소스를 컴파일 할 때 경로를 설정하여 컴파일 하게 될 것이다. 

> **참고 :**  이 파일에서는 **C:\WpdPack_4_1_2\WpdPack** 경로에 라이브러리 파일과 헤더 파일등이 존재한다는 가정하에 설명하도록 하겠다.


## 설정 변경
리눅스 환경의 경우 환경을 구축 할 때에 패키지로 설치 하였을 경우 추가적인 설정을 변경할 필요없이 바로 컴파일 하면 되지만, 윈도우 환경의 경우 part2/SConscript 파일을 환경에 맞게 수정해야 한다.

```python

#-*- coding: utf-8 -*-
import os
Import('env')

#####################################################

## 다음의 두 개 변수에 값을 입력해야 합니다. ##

pcap_header_path = 'C:\\WpdPack_4_1_2\\WpdPack\\Include'
pcap_lib_path = 'C:\\WpdPack_4_1_2\\WpdPack\\Lib'

#####################################################
```

위의 내용에서 pcap_header_path 과 pcap_lib_path  의 경로를 설정해 줘야 한다.


> **참고:** 
> 리눅스 환경의 경우 값을 지정하지 않아도 되며, 윈도우의 경우 32비트 또는 64 비트에 따라 아래와 같이 라이브러리 경로를 다르게 지정해 줘야 한다. 

```python 
pcap_lib_path = 'C:\\WpdPack_4_1_2\\WpdPack\\Lib\\x64'		//64비트일 경우
pcap_lib_path = 'C:\\WpdPack_4_1_2\\WpdPack\\Lib'			//32비트 일경우

```

## 컴파일

아래와 같은 명령어로 컴파일 하면 part1과 part2에 있는 예제 코드들이 모두 함께 컴파일 되게 되며, 각각의 예제 디렉토리안에 build 라는 디렉토리 안에 실행파일이 생성되게 된다.

> scons
