#include "stdint.h"
#include "vfs.h"
#include "malloc.h"
#include "string.h"
#include "vga.h"

VFS vfsr;

void init_vfs(VFS *vfs) {
    vfs->file_count = 0;
}

void create_file(VFS *vfs, const char *filename, const char *data)
 {
    File *file = &vfs->files[vfs->file_count];
    int name_len = strlen(filename);
    int data_len = strlen(data);
    memcpy(file->name, filename, name_len+1);
    memcpy(file->data, data, data_len+1);
    file->size = data_len;
    vfs->file_count++;
}

const char* read_file(VFS *vfs, const char* filename) {
  for(int i=0;i<vfs->file_count;i++) {
    if(strcmp(vfs->files[i].name, filename) == 0) {
        return vfs->files[i].data;
    }    
  }
  return "notp";
}

void delete_file(VFS *vfs, const char *filename) {
  File replacement;
  for(int i=0;i<vfs->file_count;i++) {
      if(strcmp(vfs->files[i].name, filename) == 0) {
            vfs->files[i] = replacement;
            vfs->file_count--;
      }   
  }
}

void print_vfs(VFS *vfs) {
    for(int i=0;i<vfs->file_count;i++) {
        print(vfs->files[i].name);
        print(" ");
    }
}

void init() {
    init_vfs(&vfsr);
}
void create(const char *filename, const char *data) {
  create_file(&vfsr, filename, data); 
}
const char *read(const char *filename) {
    return read_file(&vfsr, filename);
}
void delete(const char *filename) {
    delete_file(&vfsr, filename);
}
void printfs() {
    print_vfs(&vfsr);
}


