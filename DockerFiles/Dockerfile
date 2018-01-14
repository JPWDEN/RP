#Dockerfile for RP assessment, by Josh Walker
#Local docker ID:  f7037a4f7bff
FROM alpine:3.5

RUN apk add --no-cache build-base openssl unzip

RUN wget -O master.zip "https://github.com/JPWDEN/RP/archive/master.zip"

RUN unzip master.zip

RUN g++ /RP-master/assessment.cpp -o /RP-master/assessment

RUN /RP-master/assessment

RUN cat /RP-master/log




#FROM microsoft/windowsservercore

# Install chocolatey
#RUN @powershell -NoProfile -ExecutionPolicy unrestricted -Command "(iex ((new-object net.webclient).DownloadString('https://chocolatey.org/install.ps1'))) >$null 2>&1"

#RUN choco install visualcpp-build-tools -version 14.0.25420.1 -y

# Add msbuild to PATH
#RUN setx /M PATH "%PATH%;C:\Program Files (x86)\MSBuild\14.0\bin"

# Test msbuild can be accessed without path
#RUN msbuild -version