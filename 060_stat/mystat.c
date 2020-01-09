#include <ctype.h>
#include <grp.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

//This function is for Step 4, which create the timestamp
char * time2str(const time_t * when, long ns) {
  char * ans = malloc(128 * sizeof(*ans));
  char temp1[64];
  char temp2[32];
  const struct tm * t = localtime(when);
  strftime(temp1, 512, "%Y-%m-%d %H:%M:%S", t);
  strftime(temp2, 32, "%z", t);
  snprintf(ans, 128, "%s.%09ld %s", temp1, ns, temp2);
  return ans;
}

//function for printing out the first three lines
void printFirstThreeLines(char * name,
                          off_t size,
                          quad_t blocks,
                          u_long block_size,
                          char * fileType,
                          dev_t device1,
                          dev_t device2,
                          ino_t inode,
                          nlink_t links,
                          mode_t mode,
                          int major_dt,
                          int minor_dt) {
  //printing the first line
  if (S_ISLNK(mode)) {
    char sybLink[256];
    ssize_t sybSize = readlink(name, sybLink, 256);
    //large input handling
    if (sybSize < 256) {
      sybLink[sybSize] = '\0';
    }
    else {
      sybLink[255] = '\0';
    }
    printf("  File: %s -> %s\n", name, sybLink);
  }
  else {
    printf("  File: %s\n", name);
  }

  //printing the second line
  printf("  Size: %-10lu\tBlocks: %-10lu IO Block: %-6lu %s\n",
         size,
         blocks,
         block_size,
         fileType);

  //printing the third line
  if ((S_ISCHR(mode)) || (S_ISBLK(mode))) {
    printf("Device: %lxh/%lud\tInode: %-10lu  Links: %-5lu Device type: %d,%d\n",
           device1,
           device2,
           inode,
           links,
           major_dt,
           minor_dt);
  }
  else {
    printf(
        "Device: %lxh/%lud\tInode: %-10lu  Links: %lu\n", device1, device2, inode, links);
  }
}

//function for printing out the fourth line
void printFourth(mode_t permission,
                 char * description,
                 uid_t uId,
                 char * uName,
                 gid_t gId,
                 char * gName) {
  printf("Access: (%04o/%s)  Uid: (%5d/%8s)   Gid: (%5d/%8s)\n",
         permission,
         description,
         uId,
         uName,
         gId,
         gName);
}

//function for printing out the last four lines
void printLastFour(char * acc, char * modi, char * chan) {
  printf("Access: %s\n", acc);
  printf("Modify: %s\n", modi);
  printf("Change: %s\n", chan);
  printf(" Birth: -\n");
}

//struct for function "getFtAndD" to return both filetype and first character in description of access,
//since both of them rely on the same piece of switch cases.
struct ftypeAndDescription {
  char * type;
  char firstInDesc;
};
typedef struct ftypeAndDescription ftAndD_t;

//function for returning both filetype and first character in description of access
ftAndD_t * getFtAndD(mode_t mode) {
  ftAndD_t * ftAndD = malloc(sizeof(*ftAndD));
  //each case give back a different filetype and first character in description of access
  switch (mode & S_IFMT) {
    case S_IFBLK:
      ftAndD->type = strdup("block special file");
      ftAndD->firstInDesc = 'b';
      break;
    case S_IFCHR:
      ftAndD->type = strdup("character special file");
      ftAndD->firstInDesc = 'c';
      break;
    case S_IFDIR:
      ftAndD->type = strdup("directory");
      ftAndD->firstInDesc = 'd';
      break;
    case S_IFIFO:
      ftAndD->type = strdup("fifo");
      ftAndD->firstInDesc = 'p';
      break;
    case S_IFLNK:
      ftAndD->type = strdup("symlink");
      ftAndD->firstInDesc = 'l';
      break;
    case S_IFREG:
      ftAndD->type = strdup("regular file");
      ftAndD->firstInDesc = '-';
      break;
    case S_IFSOCK:
      ftAndD->type = strdup("socket");
      ftAndD->firstInDesc = 's';
      break;
  }
  return ftAndD;
}

//function for building the human readable access string, with length of 10
char * buildDescrip(char firstInDesc, struct stat * out, char * descrip) {
  // start to build from the first character to the tenth character
  descrip[0] = firstInDesc;

  if ((out->st_mode & S_IRUSR) != 0) {
    descrip[1] = 'r';
  }

  if ((out->st_mode & S_IWUSR) != 0) {
    descrip[2] = 'w';
  }

  if ((out->st_mode & S_IXUSR) != 0) {
    descrip[3] = 'x';
  }

  if ((out->st_mode & S_IRGRP) != 0) {
    descrip[4] = 'r';
  }

  if ((out->st_mode & S_IWGRP) != 0) {
    descrip[5] = 'w';
  }

  if ((out->st_mode & S_IXGRP) != 0) {
    descrip[6] = 'x';
  }

  if ((out->st_mode & S_IROTH) != 0) {
    descrip[7] = 'r';
  }

  if ((out->st_mode & S_IWOTH) != 0) {
    descrip[8] = 'w';
  }

  if ((out->st_mode & S_IXOTH) != 0) {
    descrip[9] = 'x';
  }
  // we don't need to put the \0 since it is originally a string
  return descrip;
}

//function for combining all helper function and print all lines
void getStat(char * name) {
  struct stat out;
  //get lstat result in the buffer called "out"
  if (lstat(name, &out) != 0) {
    perror("lstat() error");
    exit(EXIT_FAILURE);
  }
  //retrieve fileType and first char in description from the returned struct
  ftAndD_t * ftAndD = getFtAndD(out.st_mode);
  char * fileType = ftAndD->type;
  char firstInDesc = ftAndD->firstInDesc;
  //print first three lines
  printFirstThreeLines(name,
                       out.st_size,
                       out.st_blocks,
                       out.st_blksize,
                       fileType,
                       out.st_dev,
                       out.st_dev,
                       out.st_ino,
                       out.st_nlink,
                       out.st_mode,
                       major(out.st_rdev),
                       minor(out.st_rdev));
  free(fileType);
  free(ftAndD);

  //initialize the access string with all '-'s so that we don't need to handle all the '-'  case
  char descrip[11] = "----------";
  //build the access string
  buildDescrip(firstInDesc, &out, descrip);

  //retrieve ids and names and print the fourth line
  uid_t uId = out.st_uid;
  char * uName = getpwuid(uId)->pw_name;
  gid_t gId = out.st_gid;
  char * gName = getgrgid(gId)->gr_name;

  printFourth(out.st_mode & ~S_IFMT, descrip, uId, uName, gId, gName);

  //retrieve formated times and print the last four lines
  char * atime = time2str(&out.st_atime, out.st_atim.tv_nsec);
  char * mtime = time2str(&out.st_mtime, out.st_mtim.tv_nsec);
  char * ctime = time2str(&out.st_ctime, out.st_ctim.tv_nsec);
  printLastFour(atime, mtime, ctime);

  free(atime);
  free(mtime);
  free(ctime);
}

//main function for handling a number of input files
int main(int argc, char ** argv) {
  if (argc == 1) {
    fprintf(stderr, "mystat: missing operand. Usage: mystat inputFileName\n");
    return EXIT_FAILURE;
  }
  //handling every input files
  for (int i = 1; i < argc; i++) {
    getStat(argv[i]);
  }
  return EXIT_SUCCESS;
}
