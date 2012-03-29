/*-------------------------------------------------------------------------*/

#include <cstdlib>
#include <cstring>
#include <iostream>

#include <getopt.h>

#include "include/core.h"

/*-------------------------------------------------------------------------*/

String_t core::input = "input.txt";
String_t core::output = "output.root";
Bool_t core::grid = false;
Bool_t core::ER = false;
Bool_t core::SM = false;
Bool_t core::OF = false;

/*-------------------------------------------------------------------------*/

void usage(const char *name)
{
	std::cout << "Usage: " << name << " [options] file\n"
		  << "Options:\n"
		  << "  -h --help"		"\t\t\t"  "Display this information\n"
		  << "  -o --output=<file>"	"\t\t"	  "Place the output into <file>\n"
		  << "  -g --grid=<mode>"	"\t\t"	  "Use the grid <mode>=local|prun\n"
		  << "     --enable-ER"		"\t\t"	  "Enable energy rescaling\n"
		  << "     --disable-ER"	"\t\t"	  "Disable energy rescaling\n"
		  << "     --enable-SM"		"\t\t"	  "Enable smearing\n"
		  << "     --disable-SM"	"\t\t"	  "Disable smearing\n"
		  << "  -f --floodgates"	"\t\t"	  "Open floodgates\n"
		  << std::endl;

	for(core::TFltParamMap::iterator it = core::fltParamMap.begin(); it != core::fltParamMap.end(); it++)
	{
		std::cout << "     --" << (*it).first << "=<value>\t\tdefault: " << (*it).second << std::endl;
	}

	for(core::TStrParamMap::iterator it = core::strParamMap.begin(); it != core::strParamMap.end(); it++)
	{
		std::cout << "     --" << (*it).first << "=<value>\t\tdefault: " << (*it).second << std::endl;
	}

	std::cout << std::endl;
}

/*-------------------------------------------------------------------------*/

static struct option options[1024];

/*-------------------------------------------------------------------------*/

int main(int argc, char **argv)
{
	/*-----------------------------------------------------------------*/
	/* CONFIGURATION						   */
	/*-----------------------------------------------------------------*/

	core::configReset();

	if(core::configLoad("config.txt") == false)
	{
		return 1;
	}

	/*-----------------------------------------------------------------*/
	/* OPTIONS							   */
	/*-----------------------------------------------------------------*/

	size_t nr = core::fltParamMap.size() + core::strParamMap.size() + 9;

	options[nr - 9] = (struct option) {"help", 0, 0, 'h'};
	options[nr - 8] = (struct option) {"output", 1, 0, 'o'};
	options[nr - 7] = (struct option) {"grid", 1, 0, 'g'};
	options[nr - 6] = (struct option) {"enable-ER", 0, 0, 996};
	options[nr - 5] = (struct option) {"disable-ER", 0, 0, 997};
	options[nr - 4] = (struct option) {"enable-SM", 0, 0, 998};
	options[nr - 3] = (struct option) {"disable-SM", 0, 0, 999};
	options[nr - 2] = (struct option) {"floodgates", 0, 0, 'f'};
	options[nr - 1] = (struct option) {0, 0, 0, 0};

	/*-----------------------------------------------------------------*/

	int i = 0;

	const char *key;

	for(core::TFltParamMap::iterator it = core::fltParamMap.begin(); it != core::fltParamMap.end(); it++)
	{
		key = (*it).first.c_str();

		options[i] = (struct option) {key, 1, 0, i++};
	}

	for(core::TStrParamMap::iterator it = core::strParamMap.begin(); it != core::strParamMap.end(); it++)
	{
		key = (*it).first.c_str();

		options[i] = (struct option) {key, 1, 0, i++};
	}

	/*-----------------------------------------------------------------*/

	for(;;)
	{
		int c = getopt_long(argc, argv, "ho:g:", options, NULL);

		/**/ if(c == -1) {
			break;
		}

		switch(c)
		{
			case 'o':
				core::output = String_t(optarg);
				break;

			case 'g':
				/**/ if(strcasecmp(optarg, "local") == 0) {
					core::grid = false;
				}
				else if(strcasecmp(optarg, "prun") == 0) {
					core::grid = true;
				}
				else
				{
					usage(argv[0]);

					return 1;
				}

				break;

			case 996:
				core::ER = true;
				break;

			case 997:
				core::ER = false;
				break;

			case 998:
				core::SM = true;
				break;

			case 999:
				core::SM = false;
				break;

			case 'f':
				core::OF = true;
				break;

			case 'h':
				usage(argv[0]);
				return 0;

			case '?':
				usage(argv[0]);
				return 1;

			default:
				if(1)
				{
					Float_t value;

					if(sscanf(optarg, "%f", &value) != 0)
					{
						core::fltParamMap[options[c].name] = atof(optarg);
					}
					else
					{
						core::strParamMap[options[c].name] = /**/(optarg);
					}
				}

				break;
		}
	}

	/*-----------------------------------------------------------------*/

	if(argc > optind)
	{
		core::input = String_t(argv[optind]);
	}

	/*-----------------------------------------------------------------*/

	std::cout << "/*-------------------------------------------------------------------------*/" << std::endl;
	std::cout << "/* OPTIONS                                                                 */" << std::endl;
	std::cout << "/*-------------------------------------------------------------------------*/" << std::endl;

	for(core::TFltParamMap::iterator it = core::fltParamMap.begin(); it != core::fltParamMap.end(); it++)
	{
		std::cout << "  " << (*it).first << " <- " << (*it).second << std::endl;
	}

	for(core::TStrParamMap::iterator it = core::strParamMap.begin(); it != core::strParamMap.end(); it++)
	{
		std::cout << "  " << (*it).first << " <- " << (*it).second << std::endl;
	}

	std::cout << std::endl;

	/*-----------------------------------------------------------------*/

	/**/ if(core::ER == false) {
		std::cout << "ER: NO" << std::endl;
	}
	else if(core::ER != false) {
		std::cout << "ER: YES" << std::endl;
	}

	/**/ if(core::SM == false) {
		std::cout << "SM: NO" << std::endl;
	}
	else if(core::SM != false) {
		std::cout << "SM: YES" << std::endl;
	}

	/**/ if(core::grid == false) {
		std::cout << "mode: LOCAL" << std::endl;
	}
	else if(core::grid != false) {
		std::cout << "mode: @PRUN" << std::endl;
	}

	std::cout << std::endl;

	/*-----------------------------------------------------------------*/
	/* LOADER							   */
	/*-----------------------------------------------------------------*/

	TChain *chain1 = new TChain();
	TChain *chain2 = new TChain();

	if(core::loader(chain1, chain2) == false)
	{
		return 1;
	}

	/*-----------------------------------------------------------------*/
	/* CORE								   */
	/*-----------------------------------------------------------------*/

	core::execute(chain1);

	/*-----------------------------------------------------------------*/

	std::cout << "Bye..." << std::endl;

	return 0;
}

/*-------------------------------------------------------------------------*/

