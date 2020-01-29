/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_error.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjosue <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 16:01:11 by cjosue            #+#    #+#             */
/*   Updated: 2020/01/29 16:01:13 by cjosue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_ERROR_H
# define ASM_ERROR_H

# define MALLOC_ERROR	"Error! memory not allocated."
# define OPEN_ERROR		"File open error!"
# define CREATE_F_ERROR	"Create file error!"
# define EX_ERROR		"Error! Wrong file extension"
# define LEXICAL_ERROR	"Lexical error at [line - "
# define SYNTAX_ERROR	"Syntax error at token [line - "
# define INVALID_PARAM	"Invalid parameter [line - "
# define NAME_SIZE		"Champion name too long [Max length - 128]"
# define COMMENT_SIZE	"Champion name too long [Max length - 2048]"
# define LABEL_ERROR	"No such label"
# define DUPLICATE_ERR	"Command error!"

#endif
