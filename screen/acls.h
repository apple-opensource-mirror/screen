/* Copyright (c) 1993-2000
 *      Juergen Weigert (jnweiger@immd4.informatik.uni-erlangen.de)
 *      Michael Schroeder (mlschroe@immd4.informatik.uni-erlangen.de)
 * Copyright (c) 1987 Oliver Laumann
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program (see the file COPYING); if not, write to the
 * Free Software Foundation, Inc.,
 * 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA
 *
 ****************************************************************
 * RCS_ID("$Id: acls.h,v 1.1.1.1 2001/12/14 22:08:28 bbraun Exp $ FAU")
 */

#ifdef MULTIUSER

/* three known bits: */
#define ACL_EXEC 0		
#define ACL_WRITE 1
#define ACL_READ 2

#define ACL_BITS_PER_CMD 1	/* for comm.h */
#define ACL_BITS_PER_WIN 3	/* for window.h */

#define USER_CHUNK 8

#define ACLBYTE(data, w)   ((data)[(w) >> 3])
#define ACLBIT(w)   (0x80 >> ((w) & 7))

typedef unsigned char * AclBits;

/*
 * How a user joins a group.
 * Here is the node to construct one list per user.
 */
struct aclusergroup
{
  struct acluser *u;	/* the user who borrows us his rights */
  struct aclusergroup *next;
};
#endif /* MULTIUSER */

/***************
 *  ==> user.h
 */

/*
 * A User has a list of groups, and points to other users.  
 * users is the User entry of the session owner (creator)
 * and anchors all other users. Add/Delete users there.
 */
typedef struct acluser
{
  struct acluser *u_next;		/* continue the main user list */
  char u_name[20+1];		/* login name how he showed up */
  char *u_password;		/* his password (may be NullStr). */
  int  u_checkpassword;		/* nonzero if this u_password is valid */
  int  u_detachwin;		/* the window where he last detached */
  int  u_detachotherwin;	/* window that was "other" when he detached */
  int  u_Esc, u_MetaEsc;	/* the users screen escape character */
#ifdef COPY_PASTE
  char  *u_copybuffer;
  int   u_copylen;
#endif
#ifdef MULTIUSER
  int u_id;			/* a uniq index in the bitfields. */
  AclBits u_umask_w_bits[ACL_BITS_PER_WIN];	/* his window create umask */
  struct aclusergroup *u_group;	/* linked list of pointers to other users */
#endif
} User;

extern int DefaultEsc, DefaultMetaEsc;

