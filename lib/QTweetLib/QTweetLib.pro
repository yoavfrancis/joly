TEMPLATE = subdirs
SUBDIRS = sub_src # Note: chaged for Joly. Original line: SUBDIRS = sub_src sub_examples
CONFIG += ordered

sub_src.subdir = src

# sub_examples.subdir = examples # Note: commented for Joly.
