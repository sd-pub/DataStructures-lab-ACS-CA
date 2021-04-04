/*
 * Testhashtable_t.c
 * Alexandru-Cosmin Mihai
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Hashtable.h"

#define MAX_STRING_SIZE		256

typedef struct {
	char name[MAX_STRING_SIZE];
	char year[MAX_STRING_SIZE];
	char fav_subj[MAX_STRING_SIZE];
	int grade;
} info_students_t;

typedef struct {
	char name[10][MAX_STRING_SIZE];
	int size;
} list_students_t;

static void
print_prieten(info_students_t *p_info)
{
	if (p_info == NULL) {
		printf("Prieten inexistent!\n");
		return;
	}
	printf("* name: %s | ", p_info->name);
	printf("%s | ", p_info->year);
	printf("Favourite subject: %s | ", p_info->fav_subj);
	printf("grade: %d \n", p_info->grade);
}

int
main()
{
	hashtable_t *ht_students, *ht_subjects;
	info_students_t info_students[5];
	info_students_t *p_infoStudent;

	/* Initializare structuri informatii students. */
	strcpy(info_students[0].name, "Todd Chavez");
	strcpy(info_students[0].year, "year 1");
	strcpy(info_students[0].fav_subj, "Sex ED");
	info_students[0].grade = 0;

	strcpy(info_students[1].name, "Mr. Peanutbutter");
	strcpy(info_students[1].year, "year 4");
	strcpy(info_students[1].fav_subj, "Arta de a fi un baiat bun");
    info_students[1].grade = 9;

	strcpy(info_students[2].name, "Sarah Lynn");
	strcpy(info_students[2].year, "year 1");
	strcpy(info_students[2].fav_subj, "Astrologie");
    info_students[2].grade = 4;

	strcpy(info_students[3].name, "Diane Nguyen");
	strcpy(info_students[3].year, "year 2");
	strcpy(info_students[3].fav_subj, "Gastronomie");
    info_students[3].grade = 9;

	strcpy(info_students[4].name, "Bojack Horseman");
	strcpy(info_students[4].year, "year 4");
	strcpy(info_students[4].fav_subj, "Arta rularii");
    info_students[4].grade = 10;



	ht_students = ht_create(10, hash_function_string,
				compare_function_strings);

	ht_put(ht_students, "Todd Chavez", strlen("Todd Chavez") + 1, &info_students[0],
		sizeof(info_students[0]));
	p_infoStudent = ht_get(ht_students, "Todd Chavez");
	printf("# 1\n");
	printf("Output:\n");
	print_prieten(p_infoStudent);
	printf("Output asteptat:\n");
	printf("* name: Todd Chavez | year 1 | Favourite Subject: Sex ED | grade: 0 \n");

	printf("\n");

	ht_put(ht_students, "Mr. Peanutbutter", strlen("Mr. Peanutbutter") + 1, &info_students[1],
		sizeof(info_students[1]));
	p_infoStudent = ht_get(ht_students, "Mr. Peanutbutter");
	print_prieten(p_infoStudent);

	ht_put(ht_students, "Sarah Lynn", strlen("Sarah Lynn") + 1, &info_students[2],
		sizeof(info_students[2]));
	p_infoStudent = ht_get(ht_students, "Sarah Lynn");
	print_prieten(p_infoStudent);

	ht_put(ht_students, "Diane Nguyen", strlen("Diane Nguyen") + 1, &info_students[3],
		sizeof(info_students[3]));
	p_infoStudent = ht_get(ht_students, "Diane Nguyen");
	print_prieten(p_infoStudent);

	ht_put(ht_students, "Bojack Horseman", strlen("Bojack Horseman") + 1, &info_students[4],
		sizeof(info_students[4]));
	p_infoStudent = ht_get(ht_students, "Bojack Horseman");
	print_prieten(p_infoStudent);

	printf("\n");
	
	char student_name[MAX_STRING_SIZE];
	fgets(student_name, MAX_STRING_SIZE, stdin);
	student_name[strlen(student_name) - 1] = '\0';

	info_students_t *students_names = ht_get(ht_students, student_name);
	if (students_names)
		printf("* Studentul %s are grade %d\n", student_name, students_names->grade);
	else
		printf("* Studentul %s nu a fost gasit!\n", student_name);
	
	ht_subjects = ht_create(10, hash_function_string,
			compare_function_strings);

	for (int i = 0; i < 5; i++) {
		if (ht_has_key(ht_subjects, info_students[i].fav_subj)) {
			list_students_t *students = (list_students_t *) ht_get(ht_subjects, info_students[i].fav_subj);

			strcpy(students->name[students->size], info_students[i].name);
			students->size++;

		} else {
			list_students_t *students = malloc(sizeof(*students));
			strcpy(students->name[0], info_students[i].name);
			students->size = 1;

			ht_put(ht_subjects, info_students[i].fav_subj, strlen(info_students[i].fav_subj) + 1, students, sizeof(*students));
			free(students);
		}
	}

	char subject_name[MAX_STRING_SIZE];
	fgets(subject_name, MAX_STRING_SIZE, stdin);
	subject_name[strlen(subject_name) - 1] = '\0';

	list_students_t *students = (list_students_t *)ht_get(ht_subjects, subject_name);
	if (students) {
		printf("Urmatorii studenti adora materia %s:\n", subject_name);
		for (int i = 0; i < students->size; i++)
			printf("%s ", students->name[i]);
		printf("\n");
	} else {
		printf("Niciunui student nu-i place materia %s.\n", subject_name);
	}

	for (int i = 0; i < ht_students->hmax; i++) {
		ll_node_t *current = ht_students->buckets[i]->head;
		while (current) {
			info_students_t *student = ((info_t*)current->data)->value;
			char *key = strdup(((info_t *) current->data)->key); 
			current = current->next;
			
			if (student->grade < 5)
				ht_remove_entry(ht_students, key);

			free(key);
		}
	}

	printf("\n# Are nota mai mare de 5?\n");
	printf("Output: %d\n", ht_has_key(ht_students, "Bojack Horseman"));
	printf("Output asteptat: 1\n");

	printf("\n# Are nota mai mare de 5?\n");
	printf("Output: %d\n", ht_has_key(ht_students, "Todd Chavez"));
	printf("Output asteptat: 0\n");

	ht_free(ht_students);
	ht_free(ht_subjects);

	return 0;
}
