#include <stdio.h>
#include <stdlib.h>

typedef unsigned char uint8;
typedef unsigned short int uint16;
typedef unsigned int uint32;
typedef unsigned long int uint64;

typedef struct {
  uint8     e_ident[16];         /* Magic number and other info */
  uint16    e_type;              /* Object file type */
  uint16    e_machine;           /* Architecture */
  uint32    e_version;           /* Object file version */
  uint64    e_entry;             /* Entry point virtual address */
  uint64    e_phoff;             /* Program header table file offset */
  uint64    e_shoff;             /* Section header table file offset */
  uint32    e_flags;             /* Processor-specific flags */
  uint16    e_ehsize;            /* ELF header size in bytes */
  uint16    e_phentsize;         /* Program header table entry size */
  uint16    e_phnum;             /* Program header table entry count */
  uint16    e_shentsize;         /* Section header table entry size */
  uint16    e_shnum;             /* Section header table entry count */
  uint16    e_shstrndx;          /* Section header string table index */
} Elf64Hdr;

void read_elf_header(const char* elfFile, const char* outputFile) {
  Elf64Hdr header;

  FILE* file = fopen(elfFile, "rb");
  if(file) {
    // read the header
    fread(&header, 1, sizeof(header), file);

    // check so its really an elf file
    if(header.e_type == 0x7f &&
       header.e_ident[1] == 'E' &&
       header.e_ident[2] == 'L' &&
       header.e_ident[3] == 'F') {

       // write the header to the output file
       FILE* fout = fopen(outputFile, "wb");
       if(fout) {
         fwrite(&header, 1, sizeof(header), fout);
         fclose(fout);
       }
     }

    // finally close the file
    fclose(file);
  }
}

int main(int argc, char const *argv[])
{
  read_elf_header("RTOSMutex.elf","out.hex");
  return 0;
}