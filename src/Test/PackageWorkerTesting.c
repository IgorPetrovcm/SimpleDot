# include "../Application/Host.h"
# include "../Application/EnvironmentManager.h"
# include "../Application/Logging.h"
# include "../Application/PackageWorker.h"
# include <unistd.h>

# define PACKAGE_EXISTS_CHECK_EXISTING_PACKAGE is_package_exists_check_existing_package_should_return_true
# define PACKAGE_NOT_EXISTS_CHECK_EXISTING_PACKAGE is_package_exitsts_check_not_existsing_package_should_return_false
# define PACKAGE_NAME_EQUAL_NELL_CHECK_EXISTING_PACKAGE is_package_existing_check_package_name_equal_null_should_return_false

static const char* structName = "PackageWorker";
static const char* isPackageExistsFunctionName = "is_package_exists()";

void PACKAGE_EXISTS_CHECK_EXISTING_PACKAGE(Host* host);
void PACKAGE_NOT_EXISTS_CHECK_EXISTING_PACKAGE(Host* host);
void PACKAGE_NAME_EQUAL_NELL_CHECK_EXISTING_PACKAGE(Host* host);

int main(){
    Host* host = constructor_host();

    EnvironmentManager* envMngr = host->envMngr;

    envMngr->print_settings_to_file(envMngr);

    host->logging = constructor_logging(envMngr);

    envMngr->push_settings_from_file(host->pathToAppSettingsFile);

    PackageWorker* packageWorker = constructor_package_worker(host->processesManager);

    PACKAGE_EXISTS_CHECK_EXISTING_PACKAGE(host);
    PACKAGE_NOT_EXISTS_CHECK_EXISTING_PACKAGE(host);
    PACKAGE_NAME_EQUAL_NELL_CHECK_EXISTING_PACKAGE(host);
}

void PACKAGE_EXISTS_CHECK_EXISTING_PACKAGE(Host* host)
{
    PackageWorker* packageWorker = constructor_package_worker(host->processesManager);

    if (packageWorker->is_package_exists(packageWorker, "git") == -1){
        host->logging->log(LOG_ERR, "Package \"git\" not found", __FILE__, __LINE__, __TIME__);
    }
    else {
        host->logging->log(LOG_INF, "Package \"git\" found", __FILE__, __LINE__, __TIME__);
    }
}

void PACKAGE_NOT_EXISTS_CHECK_EXISTING_PACKAGE(Host* host)
{
    PackageWorker* packageWorker = constructor_package_worker(host->processesManager);

    if (packageWorker->is_package_exists(packageWorker, "gite") == -1){
        host->logging->log(LOG_INF, "Package \"gite\" not found", __FILE__, __LINE__, __TIME__);
    }
    else {
        host->logging->log(LOG_ERR, "Package \"gite\" found", __FILE__, __LINE__, __TIME__);
    }
}

void PACKAGE_NAME_EQUAL_NELL_CHECK_EXISTING_PACKAGE(Host* host)
{
PackageWorker* packageWorker = constructor_package_worker(host->processesManager);

    if (packageWorker->is_package_exists(packageWorker, NULL) == -1){
        host->logging->log(LOG_INF, "Package name equal \"null\" not found", __FILE__, __LINE__, __TIME__);
    }
    else {
        host->logging->log(LOG_ERR, "Package name equal \"null\" found", __FILE__, __LINE__, __TIME__);
    }
}