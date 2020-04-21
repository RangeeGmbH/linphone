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

#ifndef LINPHONE_DAEMON_COMMAND_JITTER_BUFFER_H_
#define LINPHONE_DAEMON_COMMAND_JITTER_BUFFER_H_

#include "daemon.h"

#define COMMANDNAME_JITTER_BUFFER "jitter-buffer"
#define COMMANDNAME_JITTER_BUFFER_RESET "jitter-buffer-reset"

using namespace::std;

class JitterBufferCommand : public DaemonCommand{
public:
	JitterBufferCommand();

	void exec(Daemon *app, const std::string& args) override;
private:
    string getJitterBufferCommandResponseStr(LinphoneCore *lc,bool audio, bool video);
};


class JitterBufferResetCommand : public DaemonCommand{
public:
	JitterBufferResetCommand();

	void exec(Daemon *app, const std::string& args) override;
};

#endif // LINPHONE_DAEMON_COMMAND_JITTER_BUFFER_H
