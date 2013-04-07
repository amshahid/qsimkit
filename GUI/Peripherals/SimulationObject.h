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

#include <QWidget>
#include <QString>
#include <QChar>
#include <QRect>
#include <map>

#include "adevs.h"

typedef adevs::PortValue<double> SimulationEvent;

// class SimulationEvent {
// 	public:
// 		SimulationEvent(int port = -1, bool high = false) : port(port), high(high) {}
// 		virtual ~SimulationEvent() {}
// 
// 		int port;
// 		bool high;
// };

typedef adevs::Bag<SimulationEvent> SimulationEventList;

class SimulationObject {
	public:
		SimulationObject() {}
		virtual ~SimulationObject() {}

		virtual void internalTransition() = 0;

		virtual void externalEvent(double t, const SimulationEventList &) = 0;

		virtual void output(SimulationEventList &output) = 0;

		virtual double timeAdvance() = 0;

};

class SimulationObjectWrapper : public adevs::Atomic<SimulationEvent> {
	public:
		SimulationObjectWrapper(SimulationObject *obj) : m_obj(obj) {}
		~SimulationObjectWrapper() {}

		/// Internal transition function.
		void delta_int();

		/// Handles external changes (change on PINs or interrupts)
		void delta_ext(double e, const SimulationEventList &xb);

		/// Confluent transition function.
		void delta_conf(const SimulationEventList &xb);

		/// Output function.
		void output_func(SimulationEventList &yb);

		/// Time advance function.
		double ta();

		/// Output value garbage collection.
		void gc_output(SimulationEventList& g);

	private:
		SimulationObject *m_obj;
};

