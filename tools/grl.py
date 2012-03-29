#!/usr/bin/python

#############################################################################
# Author  : Jerome ODIER
#
# Email   : jerome.odier@cern.ch
#
# Version : 2.0 (2010-2011)
#
#############################################################################

import sys, xml.dom.minidom

#############################################################################

if __name__ == '__main__':
	try:
		MyGRLRoot = xml.dom.minidom.parse(sys.argv[1])

	except (IndexError, IOError), e:
		print 'Syntax: grl.py grl.xml variable'
		sys.exit(1)

	i = 0

	name = sys.argv[2]

	print('%s = false;\n' % name)

	for LumiRange in MyGRLRoot.getElementsByTagName('NamedLumiRange'):

		for LumiBlock in LumiRange.getElementsByTagName('LumiBlockCollection'):

			Run = None
			LBRangeStart = []
			LBRangeEnd = []

			for theRun in LumiBlock.getElementsByTagName('Run'):
				for node in theRun.childNodes:
					Run = node.nodeValue.strip()

			for theLBRange in LumiBlock.getElementsByTagName('LBRange'):
				LBRangeStart.append(theLBRange.getAttribute('Start'))
				LBRangeEnd.append(theLBRange.getAttribute('End'))

			if not Run is None:

				nr = (len(LBRangeStart) + len(LBRangeEnd)) / 2

				if i == 0:
					print '/**/ if(RunNumber == %s && (' % Run
				else:
					print 'else if(RunNumber == %s && (' % Run

				for j in xrange(nr):
					print '\t(LumiBlock >= %4s && LumiBlock <= %4s)' % (LBRangeStart[j], LBRangeEnd[j])

					if j < (nr - 1):
						print '\t||'

				print '  )) %s = true;' % name

				i = i + 1

	print ''

#############################################################################

