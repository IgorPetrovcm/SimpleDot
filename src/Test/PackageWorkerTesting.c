# include "../Application/Host.h"
# include "../Application/EnvironmentManager.h"
# include "../Application/Logging.h"
# include "../Application/PackageWorker.h"
# include <unistd.h>
# include <stdio.h>

# define PACKAGE_EXISTS_CHECK_EXISTING_PACKAGE launch_package_manager_check_existing_package_should_return_true
# define PACKAGE_NOT_EXISTS_CHECK_EXISTING_PACKAGE launch_package_manager_check_not_existsing_package_should_return_false
# define PACKAGE_NAME_EQUAL_NELL_CHECK_EXISTING_PACKAGE launch_package_manager_check_package_name_equal_null_should_return_false
# define PACKAGE_NAME_EXISTS_INSTALL_PACKAGE launch_package_manager_install_exists_package_should_return_true
# define PACKAGE_NAME_NOT_EXISTS_DOESNT_INSTALL_PACKAGE launch_package_manager_not_exists_package_return_false
# define PACKAGE_EXISTS_UNISTALL_PACKAGE launch_package_manager_unistall_exists_package_should_return_true
# define PACKAGE_NOT_EXISTS_UNISTALL_PACKAGE launch_package_manager_unistall_not_exists_package

static const char* structName = "PackageWorker";
static const char* isPackageExistsFunctionName = "is_package_exists()";

void PACKAGE_EXISTS_CHECK_EXISTING_PACKAGE(Host* host);
void PACKAGE_NOT_EXISTS_CHECK_EXISTING_PACKAGE(Host* host);
void PACKAGE_NAME_EQUAL_NELL_CHECK_EXISTING_PACKAGE(Host* host);
void PACKAGE_NAME_EXISTS_INSTALL_PACKAGE(Host* host);
void PACKAGE_NAME_NOT_EXISTS_DOESNT_INSTALL_PACKAGE(Host* host);
void PACKAGE_EXISTS_UNISTALL_PACKAGE(Host* host);
void PACKAGE_NOT_EXISTS_UNISTALL_PACKAGE(Host* host);

int main(){
    Host* host = constructor_host();

    EnvironmentManager* envMngr = host->envMngr;

    envMngr->print_settings_to_file(envMngr);

    host->logging = constructor_logging(envMngr);

    envMngr->push_settings_from_file(envMngr);

    PACKAGE_EXISTS_CHECK_EXISTING_PACKAGE(host);
    PACKAGE_NOT_EXISTS_CHECK_EXISTING_PACKAGE(host);
    PACKAGE_NAME_EQUAL_NELL_CHECK_EXISTING_PACKAGE(host);
    PACKAGE_NAME_EXISTS_INSTALL_PACKAGE(host);
    PACKAGE_NAME_NOT_EXISTS_DOESNT_INSTALL_PACKAGE(host);
    PACKAGE_EXISTS_UNISTALL_PACKAGE(host);
    PACKAGE_NOT_EXISTS_UNISTALL_PACKAGE(host);
}

void PACKAGE_EXISTS_CHECK_EXISTING_PACKAGE(Host* host)
{
    PackageWorker* packageWorker = constructor_package_worker();

    if (packageWorker->launch_package_manager(packageWorker, CHECK_PACKAGE, "git") == -1){
        host->logging->log(LOG_ERR, "Package \"git\" not found", __FILE__, __LINE__, __TIME__);
    }
    else {
        host->logging->log(LOG_INF, "Package \"git\" found", __FILE__, __LINE__, __TIME__);
    }
}

void PACKAGE_NOT_EXISTS_CHECK_EXISTING_PACKAGE(Host* host)
{
    PackageWorker* packageWorker = constructor_package_worker();

    if (packageWorker->launch_package_manager(packageWorker, CHECK_PACKAGE, "gite") == -1){
        host->logging->log(LOG_INF, "Package \"gite\" not found", __FILE__, __LINE__, __TIME__);
    }
    else {
        host->logging->log(LOG_ERR, "Package \"gite\" found", __FILE__, __LINE__, __TIME__);
    }
}

void PACKAGE_NAME_EQUAL_NELL_CHECK_EXISTING_PACKAGE(Host* host)
{
    PackageWorker* packageWorker = constructor_package_worker();

    if (packageWorker->launch_package_manager(packageWorker, CHECK_PACKAGE, NULL) == -1){
        host->logging->log(LOG_INF, "Package name equal \"null\" not found", __FILE__, __LINE__, __TIME__);
    }
    else {
        host->logging->log(LOG_ERR, "Package name equal \"null\" found", __FILE__, __LINE__, __TIME__);
    }
}

void PACKAGE_NAME_EXISTS_INSTALL_PACKAGE(Host* host)
{
    PackageWorker* packageWorker = constructor_package_worker();

    if (packageWorker->launch_package_manager(packageWorker, INSTALL_PACKAGE, "antiword") == 0){
        host->logging->log(LOG_INF, "Package name \"antiword\" install", __FILE__, __LINE__, __TIME__);
    }
    else {
        host->logging->log(LOG_ERR, "Package name \"antiword\" not install", __FILE__, __LINE__, __TIME__);
    }
}

void PACKAGE_NAME_NOT_EXISTS_DOESNT_INSTALL_PACKAGE(Host* host)
{
    PackageWorker* packageWorker = constructor_package_worker();

    if (packageWorker->launch_package_manager(packageWorker, INSTALL_PACKAGE, "gite") == -1){
        host->logging->log(LOG_INF, "Package name \"gite\" not install", __FILE__, __LINE__, __TIME__);
    }
    else {
        host->logging->log(LOG_ERR, "Package name \"gite\" install", __FILE__, __LINE__, __TIME__);
    }
}

void PACKAGE_EXISTS_UNISTALL_PACKAGE(Host* host)
{
    PackageWorker* packageWorker = constructor_package_worker();

    if (packageWorker->launch_package_manager(packageWorker, UNISTALL_PACKAGE, "antiword") == 0){
        host->logging->log(LOG_INF, "Package name \"antiword\" unistall succesfully", __FILE__, __LINE__, __TIME__);
    }
    else {
        host->logging->log(LOG_ERR, "Package name \"antiword\" doesn't unistall", __FILE__, __LINE__, __TIME__);
    }
}

void PACKAGE_NOT_EXISTS_UNISTALL_PACKAGE(Host* host)
{
    PackageWorker* packageWorker = constructor_package_worker();

    if (packageWorker->launch_package_manager(packageWorker, UNISTALL_PACKAGE, "antiword") == -1){
        host->logging->log(LOG_INF, "Package name \"antiword\" doesn't unistall", __FILE__, __LINE__, __TIME__);        
    }
    else {
        host->logging->log(LOG_ERR, "Package name \"antiword\" unistall succesfully", __FILE__, __LINE__, __TIME__);
    }
}