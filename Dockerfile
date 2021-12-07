FROM ubuntu
RUN apt update 
RUN apt install gcc -qy
RUN mkdir scripts
COPY main.c /scripts/
RUN gcc -masm=intel -o /scripts/a.out /scripts/main.c
CMD /scripts/a.out
