/* SPDX-License-Identifier: GPL-2.0-or-later */
/* QUIC kernel implementation
 * (C) Copyright Red Hat Corp. 2023
 *
 * This file is part of the SCTP kernel implementation
 *
 * Written or modified by:
 *    Xin Long <lucien.xin@gmail.com>
 */

#ifndef __uapi_quic_h__
#define __uapi_quic_h__

#include <linux/types.h>
#include <linux/socket.h>

enum {
	IPPROTO_QUIC = 144,		/* A UDP-Based Multiplexed and Secure Transport	*/
#define IPPROTO_QUIC		IPPROTO_QUIC
};

#define SOL_QUIC	144

enum {
	QUIC_STREAM_FLAG_NEW = (1 << 0),
	QUIC_STREAM_FLAG_FIN = (1 << 1),
};

struct quic_sndinfo {
	uint32_t stream_id;
	uint32_t stream_flag;
};

struct quic_rcvinfo {
	uint32_t stream_id;
	uint32_t stream_flag;
};

enum quic_cmsg_type {
	QUIC_SNDINFO,
	QUIC_RCVINFO,
};

enum {
	QUIC_CONG_ALG_RENO,
	QUIC_CONG_ALG_MAX,
};

struct quic_connection_id {
	uint32_t number;
	uint8_t len;
	uint8_t data[20];
};

struct quic_connection_id_numbers {
	uint32_t start_number;
	uint32_t end_number;
	uint32_t active_number;
};

struct quic_transport_param {
	uint32_t max_udp_payload_size;
	uint32_t ack_delay_exponent;
	uint32_t max_ack_delay;
	uint32_t initial_max_data;
	uint32_t initial_max_stream_data_bidi_local;
	uint32_t initial_max_stream_data_bidi_remote;
	uint32_t initial_max_stream_data_uni;
	uint32_t initial_max_streams_bidi;
	uint32_t initial_max_streams_uni;
	uint32_t initial_smoothed_rtt;
};

struct quic_crypto_secret {
	uint8_t type;
	uint8_t secret[32];
};

struct quic_context {
	struct quic_transport_param	local;
	struct quic_transport_param	remote;
	struct quic_connection_id	source;
	struct quic_connection_id	dest;
	struct sockaddr_storage		src;
	struct sockaddr_storage		dst;
	struct quic_crypto_secret	send;
	struct quic_crypto_secret	recv;
	uint8_t				is_serv;
};

#define QUIC_SOCKOPT_CONTEXT				0
#define QUIC_SOCKOPT_SOURCE_CONNECTION_ID_NUMBERS	1
#define QUIC_SOCKOPT_DEST_CONNECTION_ID_NUMBERS		2
#define QUIC_SOCKOPT_KEY_UPDATE				3
#define QUIC_SOCKOPT_CONNECTION_MIGRATION		4
#define QUIC_SOCKOPT_CONGESTION_CONTROL			5

#endif /* __uapi_quic_h__ */
