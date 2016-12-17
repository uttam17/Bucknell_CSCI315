#include "read_dir.h"

struct file_stats * file_eval(char *filename);
void process(char *name);
void enqueue(char *name, que_t *q);
void dequeue(que_t *q);
void peek_front(char *name,que_t q);
bool queue_empty(que_t q);
void initq(que_t *q);

struct file_stats {
    off_t size;
    time_t mtime;
    int normal;
};

int main(int argc, char *argv[]) {
  if (2 != argc) {
    printf(" usage: %s [directory path]\n", argv[0]);
    exit(-1);
  }
  else {
    process(argv[1]);
  }
  return 0;
}

  struct file_stats * file_eval(char *filename) {
    struct file_stats *stats = malloc(sizeof(struct file_stats));
    struct stat file_info;
    int fd = open(filename, O_RDONLY);
    if (fstat(fd, &file_info) == 0) {
      stats->size = file_info.st_size;
      stats->mtime = file_info.st_mtime;
      if (S_ISREG(file_info.st_mode)) {
        stats->normal = 1;
      } 
      else {
        stats->normal = 0;
      }
    }
    close(fd);
    return stats;
}

void process(char *root){
  //Initialize variable
  int numDirectories = 0;
  int numFiles = 0;
  int numRegFiles = 0;
  time_t recMod = 0;
  char mostRecentlyMod[MAXLENGTH];
  time_t lesMod = 0;
  char leastRecentlyMod[MAXLENGTH];
  off_t smallest = 0;
  off_t largest = 0;
  off_t totalFileSize = 0;
  que_t nameq;
  char dname[MAXLENGTH];
  char cname[MAXLENGTH];
  char prefix[MAXLENGTH];
  struct stat file_info;
  int symbolicLink = 0;
  struct dirent *dp;
  struct file_stats *file_stat;
  DIR *dirp;
  initq(&nameq);
  enqueue(root,&nameq);

  while (true != queue_empty(nameq)) {
    peek_front(dname,nameq);
    dequeue(&nameq);
    symbolicLink = 0;

    if (lstat(dname, &file_info) == 0) {
      if (S_ISLNK(file_info.st_mode)) {
        symbolicLink = 1;
      }
    }

    dirp = opendir(dname);
    if ((!symbolicLink) && (dirp != NULL)) {
      numDirectories++;

      printf("directory : %s\n",dname);
      strncpy(prefix, dname, MAXLENGTH);
      strncat(prefix,"/", MAXLENGTH);

      for (dp = readdir(dirp); NULL != dp; dp = readdir(dirp)) {
        if ((strcmp(dp->d_name,"..") != 0) && (strcmp(dp->d_name,".") != 0)) {

          strncpy(cname, prefix, MAXLENGTH);
          strncat(cname, dp->d_name, MAXLENGTH);
          enqueue(cname,&nameq);
        }
      }
      closedir (dirp);
    } 
    else {
      printf("processing file: %s\n", dname);
      numFiles++;
      file_stat = file_eval(dname);
      totalFileSize += file_stat->size;
      //Updating variables for each file
      if (smallest == 0) {
        smallest = file_stat->size;
      } 
      else if (smallest > file_stat->size) {
        smallest = file_stat->size;
      }

      if (file_stat->size > largest) {
        largest = file_stat->size;
      }

      if (file_stat->normal) {
        numRegFiles++;
      }

      if (file_stat->mtime > recMod) {
        recMod = file_stat->mtime;
        strncpy(mostRecentlyMod, dname, MAXLENGTH);
      }
      if (lesMod == 0) {
        lesMod = file_stat->mtime;
      } else if (lesMod > file_stat->mtime) {
        lesMod = file_stat->mtime;
        strncpy(leastRecentlyMod, dname, MAXLENGTH);
      }
    }
  }
  int average = 0;
  average = totalFileSize/numFiles;
  //Printing out each assigned variable
  printf("==directory===== %s\n",root);
  printf("Smallest file size is %d bytes\n", (int) smallest);
  printf("Largest file size is %d bytes\n", (int) largest);
  printf("Average_size file size is %d bytes\n", average);
  printf("Total number of directories is %d\n", numDirectories);
  printf("Total number of regular files is %d\n", numRegFiles);
  printf("Most recently modified file is %s\n", mostRecentlyMod);
  printf("Least recently modified file is %s\n", leastRecentlyMod);
}

void initq(que_t *q) {
  q->head = q->tail = NULL;
}

bool queue_empty(que_t q) {
  if (NULL == q.head) {
    return true;
  } 
  else {
    return false;
  }
}

void enqueue(char *name, que_t *q) {
  item_t *temp;
  temp = (item_t *)malloc(sizeof(item_t));
  strncpy(temp->name,name,MAXLENGTH);
  temp->next = NULL;
  if (true == queue_empty(*q)) {
    q->head = temp;
    q->tail = temp;
  } else {
    q->tail->next = temp;
    q->tail = q->tail->next;
  }
}

void dequeue(que_t *q) {
  item_t *temp;
  if (true == queue_empty(*q)) {
    printf(" error in dequeue \n");
    exit(-1);
  } else {
    temp = q->head;
    q->head = q->head->next;
    free(temp);
  }
}

void peek_front(char *name, que_t q) {
  if (true == queue_empty(q)) {
    printf(" error in dequeue \n");
     exit(-1);
  } else {
    strncpy(name, q.head->name, MAXLENGTH);
  }
}

