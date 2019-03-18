#!/usr/bin/python
#coding: utf-8

import pickle
from athletelist import AthleteList

def get_coach_data(filename):
	try:
		with open(filename) as f:
			data = f.readline()
		templ = data.strip().split(',')
		return (Athlete(templ.pop(0),templ.pop(0),templ))
	except IOError as err:
		print('File open error' + str(err))
		return(None)


def put_to_store(files_list):
	all_athletes = {}
	