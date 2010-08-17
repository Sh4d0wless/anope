/* OperServ core functions
 *
 * (C) 2003-2010 Anope Team
 * Contact us at team@anope.org
 *
 * Please read COPYING and README for further details.
 *
 * Based on the original code of Epona by Lara.
 * Based on the original code of Services by Andy Church.
 */

/*************************************************************************/

#include "module.h"

class CommandOSUpdate : public Command
{
 public:
	CommandOSUpdate() : Command("UPDATE", 0, 0, "operserv/update")
	{
	}

	CommandReturn Execute(User *u, const std::vector<Anope::string> &params)
	{
		notice_lang(Config->s_OperServ, u, OPER_UPDATING);
		save_data = true;
		return MOD_CONT;
	}

	bool OnHelp(User *u, const Anope::string &subcommand)
	{
		notice_help(Config->s_OperServ, u, OPER_HELP_UPDATE);
		return true;
	}

	void OnServHelp(User *u)
	{
		notice_lang(Config->s_OperServ, u, OPER_HELP_CMD_UPDATE);
	}
};

class OSUpdate : public Module
{
	CommandOSUpdate commandosupdate;

 public:
	OSUpdate(const Anope::string &modname, const Anope::string &creator) : Module(modname, creator)
	{
		this->SetAuthor("Anope");
		this->SetType(CORE);

		this->AddCommand(OperServ, &commandosupdate);
	}
};

MODULE_INIT(OSUpdate)
