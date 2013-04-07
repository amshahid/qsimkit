/**
 * QSimKit - MSP430 simulator
 * Copyright (C) 2013 Jan "HanzZ" Kaluza (hanzz.k@gmail.com)
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 **/

#pragma once

#include <stdint.h>
#include <QList>
#include "CPU/Memory/Register.h"

class Breakpoint;
class MSP430;

class BreakpointManager : public RegisterWatcher {
	public:
		BreakpointManager();
		~BreakpointManager();

		void setCPU(MSP430 *cpu);

		void addRegisterBreak(int reg, uint16_t value);
		void removeRegisterBreak(int reg, uint16_t value);

		void addBreakpoint(Breakpoint *b);
		void removeBreakpoint(Breakpoint *b);

		bool shouldBreak();

		void breakNow() {
			m_break = true;
		}

		void handleRegisterChanged(Register *reg, int id, uint16_t value);

	private:
		MSP430 *m_cpu;
		QList<QList<uint16_t> > m_breaks;
		QList<Breakpoint *> m_breakpoints;
		bool m_break;

};

