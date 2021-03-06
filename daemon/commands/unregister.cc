/*
 * Copyright (c) 2010-2019 Belledonne Communications SARL.
 *
 * This file is part of Liblinphone.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "unregister.h"

using namespace std;

UnregisterCommand::UnregisterCommand() :
		DaemonCommand("unregister", "unregister <register_id>|ALL", "Unregister the daemon from the specified proxy or from all proxies.") {
	addExample(new DaemonCommandExample("unregister 3",
						"Status: Error\n"
						"Reason: No register with such id."));
	addExample(new DaemonCommandExample("unregister 2",
						"Status: Ok"));
	addExample(new DaemonCommandExample("unregister ALL",
						"Status: Ok"));
}

void UnregisterCommand::exec(Daemon *app, const string& args) {
	LinphoneProxyConfig *cfg = NULL;
	string param;
	int pid;
    ostringstream ost;

	istringstream ist(args);
	ist >> param;
	if (ist.fail()) {
		app->sendResponse(Response(COMMANDNAME_UNREGISTER, "Missing parameter.", Response::Error));
		return;
	}
	if (param.compare("ALL") == 0) {
		//Erase all proxies from config
        linphone_core_clear_proxy_config(app->getCore());
        linphone_core_clear_all_auth_info(app->getCore());
        ost << "All Proxies were unregistered!" << "\n";
	} else {
		ist.clear();
		ist.str(param);
		ist >> pid;
		if (ist.fail()) {
			app->sendResponse(Response(COMMANDNAME_UNREGISTER, "Incorrect parameter.", Response::Error));
			return;
		}
        cfg = app->findProxy(pid);
		if (cfg == NULL) {
			app->sendResponse(Response(COMMANDNAME_UNREGISTER, "No register with such id.", Response::Error));
			return;
		} else {
            cfg = app->findProxy(pid);
            ost << "ProxyId: " << pid << "\n" << "ProxyAddress: " << linphone_proxy_config_get_server_addr(cfg) << "\n" << "ProxyIdentity: " << linphone_proxy_config_get_identity(cfg);
        }
        linphone_core_remove_proxy_config(app->getCore(), cfg);
	}
    app->sendResponse(Response(COMMANDNAME_UNREGISTER, ost.str(), Response::Ok));
}
