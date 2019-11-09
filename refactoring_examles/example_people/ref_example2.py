#!/usr/bin/env python3
import collections
from datetime import date

Person = collections.namedtuple('Person', ['first_name', 'last_name', 'birth_date', 'area'])
people = [
    Person(first_name='Albert', last_name='Einstein', birth_date=date(year=1879, month=3, day=14), area='physics'),
    Person(first_name='Alan', last_name='Turing', birth_date=date(year=1912, month=6, day=23), area='cs'),
    Person(first_name='Edsger', last_name='Dijkstra', birth_date=date(year=1930, month=5, day=11), area='cs'),
    Person(first_name='Niels', last_name='Bohr', birth_date=date(year=1885, month=10, day=7), area='physics'),
    Person(first_name='Leslie', last_name='Lamport', birth_date=date(year=1941, month=2, day=7), area='cs'),
]

# Student's code starts.

# Add parameter for title


def print_people_in_area(area, title):
    print('--- {} ---'.format(title))
    num_people_in_area = 0
    for person in people:
        if person.area == area:
            print('* {}. {}, born on {}'.format(person.first_name[:1], person.last_name, person.birth_date))
            num_people_in_area += 1
    print('Total: {}'.format(num_people_in_area))


if __name__ == '__main__':
    print_people_in_area('physics', title='Physics')
    print()
    print_people_in_area('cs', title='Computer Science')

    oldest_person = min(people, key=lambda person: person.birth_date)
    print('Oldest person: {}. {}, born on {}'.format(oldest_person.first_name[:1], oldest_person.last_name,
                                                     oldest_person.birth_date))
