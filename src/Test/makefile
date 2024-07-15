srcParsTest:  ../Model/AppSettings.c ../Model/LoggingSettings.c \
		../Service/Host.c ../Service/EnvironmentManager.c \
		../Service/Logging.c ../Service/SourceParser.c \
		../Service/ProcessesManager.c SourceParserTesting.c bottom pkgWorkTest
	gcc ../Model/AppSettings.c ../Model/LoggingSettings.c \
		../Service/Host.c ../Service/EnvironmentManager.c \
		../Service/Logging.c ../Service/SourceParser.c \
		../Service/SettingHost.c SourceParserTesting.c  \
		../Service/ProcessesManager.c ../Bottom/bottom.so -o srcParsTest

pkgWorkTest: ../Model/AppSettings.c ../Model/LoggingSettings.c \
		../Service/Host.c ../Service/EnvironmentManager.c \
		../Service/Logging.c ../Service/PackageWorker.c \
		../Service/ProcessesManager.c SourceParserTesting.c bottom
	gcc ../Model/AppSettings.c ../Model/LoggingSettings.c \
		../Service/Host.c ../Service/EnvironmentManager.c \
		../Service/Logging.c ../Service/PackageWorker.c \
		../Service/SettingHost.c PackageWorkerTesting.c  \
		../Service/ProcessesManager.c ../Bottom/bottom.so \
		-o pkgWorkTest

bottom: ../Bottom/bottom.so
	sudo cp ../Bottom/bottom.so /lib/bottom.so

../Bottom/bottom.so: ../Bottom/matches.o
	gcc -shared ../Bottom/matches.o -o ../Bottom/bottom.so

../Bottom/matches.o: ../Bottom/matches.c
	gcc -c -fPIC ../Bottom/matches.c -o ../Bottom/matches.o

clean:
	rm -f ../Bottom/matches.o
	rm -f ../Bottom/bottom.so
	sudo rm -f /lib/bottom.so
	rm -f srcParsTest
	rm -f pkgWorkTest
