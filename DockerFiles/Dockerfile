#Dockerfile for RP assessment, by Josh Walker
#Local docker ID:  f7037a4f7bff
FROM alpine:3.5

RUN apk add --no-cache build-base openssl unzip

RUN wget -O master.zip "https://github.com/JPWDEN/RP/archive/master.zip"

RUN unzip master.zip

RUN g++ /RP-master/assessment.cpp -o /RP-master/assessment

RUN /RP-master/assessment

RUN cat /RP-master/log



#  Future option:  Create dockerfile configuration for Windows builds
#FROM microsoft/windowsservercore
