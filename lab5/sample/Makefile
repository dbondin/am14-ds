all: liblzwy_sample.so

liblzwy_sample.so: lzwy_sample.o
	g++ -shared $^ -o $@

%.o: %.cpp
	g++ -I.. -c $<

clean:
	rm -rf liblzwy_sample.so *.o
