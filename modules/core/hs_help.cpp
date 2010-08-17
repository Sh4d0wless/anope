/* HostServ core functions
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

class CommandHSHelp : public Command
{
 public:
	CommandHSHelp() : Command("HELP", 1, 1)
	{
		this->SetFlag(CFLAG_ALLOW_UNREGISTERED);
	}

	CommandReturn Execute(User *u, const std::vector<Anope::string> &params)
	{
		mod_help_cmd(HostServ, u, params[0]);
		return MOD_CONT;
	}

	void OnSyntaxError(User *u, const Anope::string &subcommand)
	{
		notice_help(Config->s_HostServ, u, HOST_HELP, Config->s_HostServ.c_str());
		for (CommandMap::const_iterator it = HostServ->Commands.begin(), it_end = HostServ->Commands.end(); it != it_end; ++it)
			if (!Config->HidePrivilegedCommands || it->second->permission.empty() || (u->Account() && u->Account()->HasCommand(it->second->permission)))
				it->second->OnServHelp(u);
	}
};

class HSHelp : public Module
{
	CommandHSHelp commandhshelp;

 public:
	HSHelp(const Anope::string &modname, const Anope::string &creator) : Module(modname, creator)
	{
		this->SetAuthor("Anope");
		this->SetType(CORE);

		this->AddCommand(HostServ, &commandhshelp);
	}
};

MODULE_INIT(HSHelp)
