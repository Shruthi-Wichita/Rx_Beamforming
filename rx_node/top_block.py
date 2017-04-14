#!/usr/bin/env python
##################################################
# Gnuradio Python Flow Graph
# Title: Top Block
# Generated: Mon Jun 10 08:50:58 2013
##################################################

from gnuradio import digital
from gnuradio import eng_notation
from gnuradio import gr
from gnuradio import uhd
from gnuradio.eng_option import eng_option
from gnuradio.gr import firdes
from gnuradio.wxgui import scopesink2
from grc_gnuradio import blks2 as grc_blks2
from grc_gnuradio import wxgui as grc_wxgui
from optparse import OptionParser
import howto
import wx

class top_block(grc_wxgui.top_block_gui):

	def __init__(self):
		grc_wxgui.top_block_gui.__init__(self, title="Top Block")
		_icon_path = "/usr/share/icons/hicolor/32x32/apps/gnuradio-grc.png"
		self.SetIcon(wx.Icon(_icon_path, wx.BITMAP_TYPE_ANY))

		##################################################
		# Variables
		##################################################
		self.samp_rate = samp_rate = 200000

		##################################################
		# Blocks
		##################################################
		self.wxgui_scopesink2_0 = scopesink2.scope_sink_f(
			self.GetWin(),
			title="Scope Plot",
			sample_rate=samp_rate,
			v_scale=0,
			v_offset=0,
			t_scale=0,
			ac_couple=False,
			xy_mode=False,
			num_inputs=1,
			trig_mode=gr.gr_TRIG_MODE_AUTO,
			y_axis_label="Counts",
		)
		self.Add(self.wxgui_scopesink2_0.win)
		self.uhd_usrp_source_0 = uhd.usrp_source(
			device_addr="addr=192.168.10.2",
			stream_args=uhd.stream_args(
				cpu_format="fc32",
				channels=range(1),
			),
		)
		self.uhd_usrp_source_0.set_clock_source("external", 0)
		self.uhd_usrp_source_0.set_samp_rate(samp_rate)
		self.uhd_usrp_source_0.set_center_freq(uhd.tune_request(908e6, dsp_freq=0, dsp_freq_policy=uhd.tune_request.POLICY_MANUAL), 0)
		self.uhd_usrp_source_0.set_gain(10, 0)
		self.uhd_usrp_source_0.set_antenna("RX2", 0)
		self.uhd_usrp_sink_0 = uhd.usrp_sink(
			device_addr="addr=192.168.10.2",
			stream_args=uhd.stream_args(
				cpu_format="fc32",
				channels=range(1),
			),
		)
		self.uhd_usrp_sink_0.set_clock_source("external", 0)
		self.uhd_usrp_sink_0.set_samp_rate(samp_rate)
		self.uhd_usrp_sink_0.set_center_freq(uhd.tune_request(928e6, rf_freq=908e6, rf_freq_policy=uhd.tune_request.POLICY_MANUAL), 0)
		self.uhd_usrp_sink_0.set_gain(0, 0)
		self.uhd_usrp_sink_0.set_antenna("TX/RX", 0)
		self.low_pass_filter_0 = gr.fir_filter_ccf(1, firdes.low_pass(
			1, samp_rate, 25000, 5000, firdes.WIN_HAMMING, 6.76))
		self.howto_rxbf_feedb_cf_0 = howto.rxbf_feedb_cf(samp_rate, 0.00025, 10000, 800, 10000, 1.5, 0.020)
		self.gr_complex_to_mag_0 = gr.complex_to_mag(1)
		self.digital_gmsk_mod_0 = digital.gmsk_mod(
			samples_per_symbol=2,
			bt=0.35,
			verbose=False,
			log=False,
		)
		self.blks2_packet_encoder_0 = grc_blks2.packet_mod_f(grc_blks2.packet_encoder(
				samples_per_symbol=2,
				bits_per_symbol=1,
				access_code="",
				pad_for_usrp=True,
			),
			payload_length=4,
		)

		##################################################
		# Connections
		##################################################
		self.connect((self.low_pass_filter_0, 0), (self.howto_rxbf_feedb_cf_0, 0))
		self.connect((self.low_pass_filter_0, 0), (self.gr_complex_to_mag_0, 0))
		self.connect((self.uhd_usrp_source_0, 0), (self.low_pass_filter_0, 0))
		self.connect((self.howto_rxbf_feedb_cf_0, 0), (self.blks2_packet_encoder_0, 0))
		self.connect((self.blks2_packet_encoder_0, 0), (self.digital_gmsk_mod_0, 0))
		self.connect((self.digital_gmsk_mod_0, 0), (self.uhd_usrp_sink_0, 0))
		self.connect((self.gr_complex_to_mag_0, 0), (self.wxgui_scopesink2_0, 0))

	def get_samp_rate(self):
		return self.samp_rate

	def set_samp_rate(self, samp_rate):
		self.samp_rate = samp_rate
		self.uhd_usrp_sink_0.set_samp_rate(self.samp_rate)
		self.low_pass_filter_0.set_taps(firdes.low_pass(1, self.samp_rate, 25000, 5000, firdes.WIN_HAMMING, 6.76))
		self.wxgui_scopesink2_0.set_sample_rate(self.samp_rate)
		self.uhd_usrp_source_0.set_samp_rate(self.samp_rate)

if __name__ == '__main__':
	parser = OptionParser(option_class=eng_option, usage="%prog: [options]")
	(options, args) = parser.parse_args()
	tb = top_block()
	tb.Run(True)

