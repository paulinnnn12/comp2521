
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Fs.h"

int helper(File node) {
	if(node == NULL) {
		return 0;
	}
	if (node->type == DIRECTORY) {
		int size = 0;
		if (node->files != NULL) {
			FileList curr = node->files;
			while(curr != NULL) {
				size += helper(curr->file);
				curr = curr->next;
			}
		}
		return size;
	} else {
		return strlen(node->text);
	}

}
int totalTextSize(Fs fs) {

	return helper(fs->root);
}

