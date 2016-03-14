/*
 * Copyright (c) 2016 Martin Pieuchot <mpi@openbsd.org>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

/*
 * CTF ``Compact ANSI-C Type Format'' ABI header file.
 */

struct ctf_header {
	unsigned short		cth_magic;
	unsigned char		cth_version;
	unsigned char		cth_flags;
	unsigned int		cth_parlabel;
	unsigned int		cth_parname;
	unsigned int		cth_lbloff;
	unsigned int		cth_objtoff;
	unsigned int		cth_funcoff;
	unsigned int		cth_typeoff;
	unsigned int		cth_stroff;
	unsigned int		cth_strlen;
};

#define CTF_F_COMPRESS		(1 << 0)	/* zlib compression */

struct ctf_lblent {
	unsigned int		ctl_label;
	unsigned int		ctl_typeidx;
};

struct ctf_stype {
	unsigned int		cts_name;
	unsigned short		cts_info;
	union {
		unsigned short _size;
		unsigned short _type;
	} _ST;
#define cts_size _ST._size
#define cts_type _ST._type
};

struct ctf_array {
	unsigned short		cta_contents;
	unsigned short		cta_index;
	unsigned int		cta_nelems;
};

struct ctf_member {
	unsigned int		ctm_name;
	unsigned short		ctm_type;
	unsigned short		ctm_offset;
};

struct ctf_lmember {
	struct ctf_member	_ctlm_member;
#define ctlm_name _ctlm_member.ctm_name
#define ctlm_type _ctlm_member.ctlm_type
#define ctlm_pad0 _ctlm_member.ctm_offset
	unsigned int		ctlm_offsethi;
	unsigned int		ctlm_offsetlo;
};

#define CTF_LSTRUCT_THRESH	8192

struct ctf_enum {
	unsigned int		cte_name;
	int			cte_value;
};

#define CTF_MAGIC		0xcff1
#define CTF_VERSION		2

#define CTF_MAX_NAME		0x7fffffff
#define CTF_MAX_VLEN		0x03ff

#define CTF_STRTAB_0		0
#define CTF_STRTAB_1		1

/*
 * Info macro.
 */
#define CTF_INFO_VLEN(i)	(((i) & CTF_MAX_VLEN))
#define CTF_INFO_ISROOT(i)	(((i) & 0x0400) >> 10)
#define CTF_INFO_KIND(i)	(((i) & 0xf800) >> 11)
#define  CTF_K_UNKNOWN		0
#define  CTF_K_INTEGER		1
#define  CTF_K_FLOAT		2
#define  CTF_K_POINTER		3
#define  CTF_K_ARRAY		4
#define  CTF_K_FUNCTION		5
#define  CTF_K_STRUCT		6
#define  CTF_K_UNION		7
#define  CTF_K_ENUM		8
#define  CTF_K_FORWARD		9
#define  CTF_K_TYPEDEF		10
#define  CTF_K_VOLATILE		11
#define  CTF_K_CONST		12
#define  CTF_K_RESTRICT		13
#define  CTF_K_MAX		31

/*
 * Name reference macro.
 */
#define CTF_NAME_STID(n)	((n) >> 31)
#define CTF_NAME_OFFSET(n)	((n) & CTF_MAX_NAME)
