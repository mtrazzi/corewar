/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkirsch <pkirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:33:27 by zaz               #+#    #+#             */
/*   Updated: 2017/09/03 12:20:00 by pkirsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Toutes les tailles sont en octets.
** On part du principe qu'un int fait 32 bits. Est-ce vrai chez vous ?
*/

#define IND_SIZE				2
#define REG_SIZE				4
#define DIR_SIZE				REG_SIZE//==4


# define REG_CODE				1
# define DIR_CODE				2
# define IND_CODE				3
# define NOT_A_PARAM_CODE		0


#define MAX_ARGS_NUMBER			4//block to 4 max
#define MAX_PLAYERS				4
#define MEM_SIZE				(4*1024)       //== 4096
#define IDX_MOD					(MEM_SIZE / 8) //== 512
#define CHAMP_MAX_SIZE			(MEM_SIZE / 6) //== 682

#define COMMENT_CHAR			'#'
#define COMMENT_CHAR2			';'
#define LABEL_CHAR				':'
#define DIRECT_CHAR				'%'
#define SEPARATOR_CHAR			','
//added
#define REG_CHAR				'r'

#define LABEL_CHARS				"abcdefghijklmnopqrstuvwxyz_0123456789"

#define NAME_CMD_STRING			".name"
#define COMMENT_CMD_STRING		".comment"

#define REG_NUMBER				16

#define CYCLE_TO_DIE			1536
#define CYCLE_DELTA				50
#define NBR_LIVE				21
#define MAX_CHECKS				10

/*
**
*/

typedef char	t_arg_type;

#define T_REG					1
#define T_DIR					2
#define T_IND					4
#define T_LAB					8//?10  8 + 2
#define T_NOTHING				0//not used

// #define T_LAB 8

// #define T_DLAB T_LAB | T_DIR
// #define	T_ILAB T_LAB | T_IND

/*
**
*/

# define PROG_NAME_LENGTH		(128 + 4) //8 lignes de 16 octets
# define COMMENT_LENGTH			(2048 + 5)
# define COREWAR_EXEC_MAGIC		0xea83f3

typedef struct					header_s
{
    unsigned int				magic;
    char						prog_name[PROG_NAME_LENGTH + 1];
    unsigned int				prog_size;
    char						comment[COMMENT_LENGTH + 1];
}								header_t;


