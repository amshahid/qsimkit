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

#include "Oscillator.h"
#include "Clock.h"

#include <stdint.h>
#include <string>
#include <vector>
#include "CPU/Memory/Memory.h"

class Variant;

namespace MSP430 {

class VLO;
class LFXT1;
class Oscillator;

class ACLK : public Clock, public OscillatorHandler, public MemoryWatcher {
	public:
		ACLK(Memory *mem, Variant *variant, VLO *vlo, LFXT1 *lfxt1);
		virtual ~ACLK();

		void handleMemoryChanged(::Memory *memory, uint16_t address);

		unsigned long getFrequency();

		std::string getSourceName();

		void reset();

		void tickRising();
		void tickFalling();

	private:
		Memory *m_mem;
		Variant *m_variant;
		Oscillator *m_source;
		VLO *m_vlo;
		LFXT1 *m_lfxt1;
		uint8_t m_divider;
		uint8_t m_counter;
		bool m_rising;
};

}
