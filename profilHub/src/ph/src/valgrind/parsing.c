/**
 * API to handle the use of valgrind and its various tools
 * - parsing stuff -
 * Copyright (C) 2013  Clement Rey <cr.rey.clement@gmail.com>
 *
 * This file is part of profilHub.
 *
 * profilHub is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
**/

#include <valgrind/parsing.h>
#include <libxml/xmlreader.h>
#include <data_structures.h>
#include <valgrind/data_structures.h>

static inline
void
__process_memcheck_node(xmlTextReader* reader)
{
	const xmlChar*	name = NULL;
	const xmlChar*	content = NULL;

	if (!(name = xmlTextReaderConstName(reader)))
	{
		name = BAD_CAST "unnamed";
//		M_ERROR("node has no name\n", 0);
	}
	if (!(content = xmlTextReaderConstValue(reader)))
	{
//		M_ERROR("node has no content\n", 0);
	}
#ifdef	D_DEBUG_ON
	printf("Depth = %d\nType = %d\nName = %s\nEmpty = %d\nHas value = %d\n",
	       xmlTextReaderDepth(reader),
	       xmlTextReaderNodeType(reader),
	       name,
	       xmlTextReaderIsEmptyElement(reader),
	       xmlTextReaderHasValue(reader));
	printf("content: '");
	if (xmlStrlen(content) > 40)
		printf("%.40s...", content);
	else
		printf("%s", content);
	printf("'\n\n");
#endif
}

bool
valgrind_parse_memcheck(int fd)
{
	xmlTextReader*	reader;
	int		ret;

	if (fd < 2)
		return M_ERROR_BOOL(false, "invalid fd\n", 0);
	LIBXML_TEST_VERSION;
	if (!(reader = xmlReaderForFd(fd, NULL, NULL, 0)))
	{
		xmlCleanupParser();
		return M_ERROR_BOOL(false, "could not create XML_READER\n", 0);
	}
	while ((ret = xmlTextReaderRead(reader)) > 0)
		__process_memcheck_node(reader);
	xmlFreeTextReader(reader);
	xmlCleanupParser();
	if (ret == -1)
		return M_ERROR_BOOL(false, "crashed while parsing XML content\n", 0);
	return true;
}
