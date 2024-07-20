srcParsTest:  ../Model/AppSettings.c ../Model/LoggingSettings.c \
		../Service/Host.c ../Service/EnvironmentManager.c \
		../Service/Logging.c ../Service/SourceParser.c \
		SourceParserTesting.c pkgWorkTest
	gcc ../Model/AppSettings.c ../Model/LoggingSettings.c \
		../Service/Host.c ../Service/EnvironmentManager.c \
		../Service/Logging.c ../Service/SourceParser.c \
		../Service/SettingHost.c SourceParserTesting.c  \
		-lsmdbottom -o srcParsTest

pkgWorkTest: ../Model/AppSettings.c ../Model/LoggingSettings.c \
		../Service/Host.c ../Service/EnvironmentManager.c \
		../Service/Logging.c ../Service/PackageWorker.c \
		SourceParserTesting.c
	gcc ../Model/AppSettings.c ../Model/LoggingSettings.c \
		../Service/Host.c ../Service/EnvironmentManager.c \
		../Service/Logging.c ../Service/PackageWorker.c \
		../Service/SettingHost.c PackageWorkerTesting.c  \
		-lsmdbottom \
		-o pkgWorkTest

clean:
	rm -f srcParsTest
	rm -f pkgWorkTest
