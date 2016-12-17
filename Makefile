TARGET = hiho
OBJECTS = hiho_67.o
CC = g++
CPPFLAGS = -g -Wall

$(TARGET) : $(OBJECTS)
	$(CC) -o $(TARGET) $(OBJECTS)

#%.d : %.cpp
#	@set -e; rm -f $@; \
	echo "====Generate .d files====";	\
	$(CC) -MM $(CPPFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o : ,g' < $@.$$$$ > $@; \
	echo "	$(CC) -c $(CPPFLAGS) $< -o $*.o" >> $@;	\
	rm -f $@.$$$$

%.d : %.cpp
	@$(CC) -MM $(CPPFLAGS) $< > $@

%.o : %.cpp
	$(CC) -c $(CPPFLAGS) $< -o $@

ifneq ($(MAKECMDGOALS), clean)
-include $(OBJECTS:.o=.d)
endif

.PHONY:clean
clean: 
	rm -f $(TARGET) *.o *.d *.d.*
