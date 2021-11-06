CC = g++
H = Monitor_Class.h Sensor_Class.h Blood_Pressure_Alert.h Body_Temp_Alert.h Pulse_Rate_Alert.h Respiration_Rate_Alert.h
C = main.cpp Monitor_Class.cpp Sensor_Class.cpp Blood_Pressure_Alert.cpp Body_Temp_Alert.cpp Pulse_Rate_Alert.cpp Respiration_Rate_Alert.cpp
EXEC = main

build: ${C} ${H}
	${CC} -o ${EXEC} ${C} `pkg-config --cflags --libs gtk+-2.0`

test:
	./${EXEC}

clean:
	rm -f ${EXEC}