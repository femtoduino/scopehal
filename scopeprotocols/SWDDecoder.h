/***********************************************************************************************************************
*                                                                                                                      *
* libscopeprotocols                                                                                                    *
*                                                                                                                      *
* Copyright (c) 2012-2022 Andrew D. Zonenberg and contributors                                                         *
* All rights reserved.                                                                                                 *
*                                                                                                                      *
* Redistribution and use in source and binary forms, with or without modification, are permitted provided that the     *
* following conditions are met:                                                                                        *
*                                                                                                                      *
*    * Redistributions of source code must retain the above copyright notice, this list of conditions, and the         *
*      following disclaimer.                                                                                           *
*                                                                                                                      *
*    * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the       *
*      following disclaimer in the documentation and/or other materials provided with the distribution.                *
*                                                                                                                      *
*    * Neither the name of the author nor the names of any contributors may be used to endorse or promote products     *
*      derived from this software without specific prior written permission.                                           *
*                                                                                                                      *
* THIS SOFTWARE IS PROVIDED BY THE AUTHORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED   *
* TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL *
* THE AUTHORS BE HELD LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES        *
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR       *
* BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT *
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE       *
* POSSIBILITY OF SUCH DAMAGE.                                                                                          *
*                                                                                                                      *
***********************************************************************************************************************/

/**
	@file
	@author Andrew D. Zonenberg
	@brief Declaration of SWDDecoder
 */

#ifndef SWDDecoder_h
#define SWDDecoder_h

class SWDSymbol
{
public:
	enum stype
	{
		TYPE_START,
		TYPE_LINERESET,
		TYPE_AP_NDP,
		TYPE_R_NW,
		TYPE_ADDRESS,
		TYPE_PARITY_OK,
		TYPE_PARITY_BAD,
		TYPE_STOP,
		TYPE_PARK,
		TYPE_TURNAROUND,
		TYPE_ACK,
		TYPE_DATA,
		TYPE_SWDTOJTAG,
		TYPE_JTAGTOSWD,
		TYPE_SWDTODORMANT,
		TYPE_LEAVEDORMANT,
		TYPE_ERROR
	};

	SWDSymbol() {}

	SWDSymbol(stype t, uint32_t d) : m_stype(t), m_data(d) {}

	stype m_stype;
	uint32_t m_data;

	bool operator==(const SWDSymbol& s) const { return (m_stype == s.m_stype) && (m_data == s.m_data); }
};

typedef Waveform<SWDSymbol> SWDWaveform;

class SWDDecoder : public Filter
{
private:
	// Magic numbers for the SWD protocol
	static const uint16_t c_JTAG_TO_SWD_SEQ;
	static const uint16_t c_SWD_TO_JTAG_SEQ;
	static const uint16_t c_SWD_TO_DORMANT_SEQ;
	static const uint32_t c_magic_seqlen;
	static const uint32_t c_reset_minseqlen;
	static const uint32_t c_magic_wakeuplen;
	static const uint8_t c_wakeup[16];

public:
	SWDDecoder(const std::string& color);

	virtual std::string GetText(int i);
	virtual Gdk::Color GetColor(int i);

	virtual void Refresh();

	static std::string GetProtocolName();

	virtual bool ValidateChannel(size_t i, StreamDescriptor stream);

	PROTOCOL_DECODER_INITPROC(SWDDecoder)
};

#endif
