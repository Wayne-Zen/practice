# python sort_table.py -i Batch2/seq_count_table.txt -o Batch2/seq_count_table_sorted.txt -k -m '^(.+)_S\d+$'

import re
import argparse
import textwrap
from collections import OrderedDict 

class CustomFormatter(argparse.ArgumentDefaultsHelpFormatter, 
                      argparse.RawTextHelpFormatter):
   pass

def my_int(x):
    res = 0
    try:
        res = int(x)
    except ValueError:
        pass

    return res

parser = argparse.ArgumentParser(formatter_class=CustomFormatter, 
                                 description='Sort the input table in human readable fashion')
parser.add_argument('-i', '--input_fp', required=True, help='input file path')
parser.add_argument('-o', '--output_fp', required=True, help='output file path')
parser.add_argument('-c', '--column_index', type=int, default=0,
                    help='sorting based column, accept integer, start from 0')
parser.add_argument('-s', '--sep', default='\t',
                    help='table field seperator')
parser.add_argument('-k', '--skip_header', action='store_true',
                    help='exclude header line when sorting')
parser.add_argument('-m', '--matching_regex', required=True,
                    help=textwrap.dedent('''\
                        matching regular expression for sorting key,
                        use () to indicate group.
                    '''))
parser.add_argument('-f', '--function', choices=['str', 'int', 'my_int'], default='my_int',
                    help='function applied to maching group')
args = parser.parse_args()


key2row = {}
with open(args.input_fp) as fi, open(args.output_fp, 'w') as fo:
    if args.skip_header:
        fo.write(fi.readline())
    for line in fi:
        content = line.strip().split(args.sep)
        key_text = content[args.column_index]
        m = re.match(args.matching_regex, key_text)
        if not m:
            raise RuntimeError('regex provided "%s" does not match text field "%s"' \
                                % (args.matching_regex, key_text))
        func = eval(args.function)
        dict_key = func(m.group(1))
        key2row[dict_key] = line.strip()

    key2row = OrderedDict(sorted(key2row.items(), key=lambda t: t[0]))
    for key in key2row:
        fo.write('%s\n' % key2row[key])
