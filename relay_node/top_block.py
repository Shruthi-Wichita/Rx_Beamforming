#!/usr/bin/env python
##################################################
# Gnuradio Python Flow Graph
# Title: Top Block
# Generated: Mon Jun 10 08:55:18 2013
##################################################

from gnuradio import digital
from gnuradio import eng_notation
from gnuradio import gr
from gnuradio import uhd
from gnuradio.eng_option import eng_option
from gnuradio.gr import firdes
from grc_gnuradio import blks2 as grc_blks2
from optparse import OptionParser
import howto
import threading
import time

class top_block(gr.top_block):

	def __init__(self):
		gr.top_block.__init__(self, "Top Block")

		##################################################
		# Variables
		##################################################
		self.samp_rate = samp_rate = 200000
		self.bf_weight = bf_weight = 1

		##################################################
		# Blocks
		##################################################
		self.howto_rxbf_randphpert_f_0 = howto.rxbf_randphpert_f(10, 1)
		def _bf_weight_probe():
			while True:
				val = self.howto_rxbf_randphpert_f_0.poll_complex_gain()
				try: self.set_bf_weight(val)
				except AttributeError, e: pass
				time.sleep(1.0/(200000))
		_bf_weight_thread = threading.Thread(target=_bf_weight_probe)
		_bf_weight_thread.daemon = True
		_bf_weight_thread.start()
		self.uhd_usrp_source_0 = uhd.usrp_source(
			device_addr="addr=192.168.10.2",
			io_type=uhd.io_type.COMPLEX_FLOAT32,
			num_channels=2,
		)
		self.uhd_usrp_source_0.set_clock_config(uhd.clock_config.external(), 0)
		self.uhd_usrp_source_0.set_subdev_spec("A:0 A:0", 0)
		self.uhd_usrp_source_0.set_samp_rate(samp_rate)
		self.uhd_usrp_source_0.set_center_freq(uhd.tune_request(908e6, rf_freq=908e6, rf_freq_policy=uhd.tune_request.POLICY_MANUAL, dsp_freq=0, dsp_freq_policy=uhd.tune_request.POLICY_MANUAL), 0)
		self.uhd_usrp_source_0.set_gain(30, 0)
		self.uhd_usrp_source_0.set_antenna("RX2", 0)
		self.uhd_usrp_source_0.set_center_freq(uhd.tune_request(928e6, rf_freq=908e6, rf_freq_policy=uhd.tune_request.POLICY_MANUAL), 1)
		self.uhd_usrp_source_0.set_gain(30, 1)
		self.uhd_usrp_source_0.set_antenna("RX2", 1)
		self.uhd_usrp_sink_0 = uhd.usrp_sink(
			device_addr="addr=192.168.10.2",
			io_type=uhd.io_type.COMPLEX_FLOAT32,
			num_channels=1,
		)
		self.uhd_usrp_sink_0.set_clock_config(uhd.clock_config.external(), 0)
		self.uhd_usrp_sink_0.set_samp_rate(samp_rate)
		self.uhd_usrp_sink_0.set_center_freq(uhd.tune_request(908e6, dsp_freq=0, dsp_freq_policy=uhd.tune_request.POLICY_MANUAL), 0)
		self.uhd_usrp_sink_0.set_gain(0, 0)
		self.uhd_usrp_sink_0.set_antenna("TX/RX", 0)
		self.low_pass_filter_1 = gr.fir_filter_ccf(1, firdes.low_pass(
			1, samp_rate, 75000, 25000, firdes.WIN_HAMMING, 6.76))
		self.low_pass_filter_0 = gr.fir_filter_ccf(1, firdes.low_pass(
			1, samp_rate, 30000, 20000, firdes.WIN_HAMMING, 6.76))
		self.howto_rxbf_forward2_cc_0 = howto.rxbf_forward2_cc(samp_rate, 0.005, 0.100, 0.020, 0.050, 1000, 20, 1000)
		self.howto_bfweight2_cc_0 = howto.bfweight2_cc(bf_weight*0.9)
		self.gr_sig_source_x_0 = gr.sig_source_c(samp_rate, gr.GR_COS_WAVE, 1000, 1, 0)
		self.gr_null_sink_0 = gr.null_sink(gr.sizeof_gr_complex*1)
		self.gr_multiply_xx_0 = gr.multiply_vcc(1)
		self.digital_gmsk_demod_0 = digital.gmsk_demod(
			samples_per_symbol=2,
			gain_mu=0.175,
			mu=0.5,
			omega_relative_limit=0.005,
			freq_error=0.0,
			verbose=False,
			log=False,
		)
		self.blks2_packet_decoder_0 = grc_blks2.packet_demod_f(grc_blks2.packet_decoder(
				access_code="",
				threshold=-1,
				callback=lambda ok, payload: self.blks2_packet_decoder_0.recv_pkt(ok, payload),
			),
		)

		##################################################
		# Connections
		##################################################
		self.connect((self.uhd_usrp_source_0, 0), (self.low_pass_filter_0, 0))
		self.connect((self.howto_bfweight2_cc_0, 0), (self.uhd_usrp_sink_0, 0))
		self.connect((self.gr_sig_source_x_0, 0), (self.gr_multiply_xx_0, 1))
		self.connect((self.uhd_usrp_source_0, 1), (self.gr_multiply_xx_0, 0))
		self.connect((self.low_pass_filter_1, 0), (self.digital_gmsk_demod_0, 0))
		self.connect((self.gr_multiply_xx_0, 0), (self.low_pass_filter_1, 0))
		self.connect((self.blks2_packet_decoder_0, 0), (self.howto_rxbf_randphpert_f_0, 0))
		self.connect((self.digital_gmsk_demod_0, 0), (self.blks2_packet_decoder_0, 0))
		self.connect((self.howto_bfweight2_cc_0, 0), (self.gr_null_sink_0, 0))
		self.connect((self.low_pass_filter_0, 0), (self.howto_rxbf_forward2_cc_0, 0))
		self.connect((self.howto_rxbf_forward2_cc_0, 0), (self.howto_bfweight2_cc_0, 0))

	def get_samp_rate(self):
		return self.samp_rate

	def set_samp_rate(self, samp_rate):
		self.samp_rate = samp_rate
		self.low_pass_filter_1.set_taps(firdes.low_pass(1, self.samp_rate, 75000, 25000, firdes.WIN_HAMMING, 6.76))
		self.gr_sig_source_x_0.set_sampling_freq(self.samp_rate)
		self.low_pass_filter_0.set_taps(firdes.low_pass(1, self.samp_rate, 30000, 20000, firdes.WIN_HAMMING, 6.76))
		self.uhd_usrp_sink_0.set_samp_rate(self.samp_rate)
		self.uhd_usrp_source_0.set_samp_rate(self.samp_rate)

	def get_bf_weight(self):
		return self.bf_weight

	def set_bf_weight(self, bf_weight):
		self.bf_weight = bf_weight
		self.howto_bfweight2_cc_0.set_bf_weight(self.bf_weight*0.9)

if __name__ == '__main__':
	parser = OptionParser(option_class=eng_option, usage="%prog: [options]")
	(options, args) = parser.parse_args()
	tb = top_block()
	tb.start()
	raw_input('Press Enter to quit: ')
	tb.stop()

