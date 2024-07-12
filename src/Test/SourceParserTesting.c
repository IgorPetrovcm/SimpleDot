# include "../Application/Host.h"
# include "../Application/EnvironmentManager.h"
# include "../Application/Logging.h"
# include "../Application/SourceParser.h"
# include <stdio.h>
# include <stdlib.h>

# define FIRST_PACK_MATCHES_THAT_EXISTS get_dir_by_matches_exists_matches
# define SECOND_PACK_MATCHES_THAT_NOT_EXISTS get_dir_by_matches_not_exists_matches

void FIRST_PACK_MATCHES_THAT_EXISTS(SourceParser* srcParser);

void SECOND_PACK_MATCHES_THAT_NOT_EXISTS(SourceParser* srcParser);

int main()
{
    Host* host = constructor_host();

    EnvironmentManager* envMngr = host->envMngr;

    envMngr->print_settings_to_file(envMngr);

    host->logging = constructor_logging(envMngr);

    envMngr->push_settings_from_file(envMngr);

    SourceParser* srcParser = constructor_source_parser("./SourceParserTestingTestExamples/first_pack", host->logging);

    FIRST_PACK_MATCHES_THAT_EXISTS(srcParser);
    SECOND_PACK_MATCHES_THAT_NOT_EXISTS(srcParser);
}

void FIRST_PACK_MATCHES_THAT_EXISTS(SourceParser* srcParser)
{
    char** result = malloc(sizeof(char*));
    *result = malloc(256);
    
    srcParser->get_dir_by_matches(srcParser, result, 3, "cfg", ".configs", "config");

    if (*result == NULL){
        srcParser->logging->log(LOG_ERR, "\"config\" directory did not match", __FILE__, __LINE__, __TIME__);
    }
    else {
        srcParser->logging->log(LOG_INF, "\"config\" directory matches", __FILE__, __LINE__, __TIME__);
    }

}

void SECOND_PACK_MATCHES_THAT_NOT_EXISTS(SourceParser* srcParser)
{
    char** result = malloc(sizeof(char*));
    *result = malloc(256);

    srcParser->get_dir_by_matches(srcParser, result, 5, "d", "s", "confi", ".", ".configs");

    if (*result == NULL){
        srcParser->logging->log(LOG_INF, "\"config\" directory did not match", __FILE__, __LINE__, __TIME__);
    }
    else {
        srcParser->logging->log(LOG_ERR, "\"config\" directory matches", __FILE__, __LINE__, __TIME__);
    }
}
