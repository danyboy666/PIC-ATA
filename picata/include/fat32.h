/*-------------------------------------------------------------------
Name......... fat32.h
Author....... Ed Langley
Date......... 29/11/2006
Description.. Header file for a driver to read a FAT32 FS over an ATA
............. interface on a PIC MCU
-------------------------------------------------------------------*/

// TODO: move this stuff into .c:

/* MBR & BPB/Volume ID stuff */
#define MBR_SIG_OFFSET_BYTES             510
#define MBR_SIG1                         0x55
#define MBR_SIG2                         0xAA
#define MBR_PART_OFFSET_BYTES            446
#define PART_TYPE_OFFSET_BYTES           4
#define PART_LBABEGIN_OFFSET_BYTES       3
#define MBR_FAT32_PART_SIG1              0x0B
#define MBR_FAT32_PART_SIG2              0x0C

#define BPB_SEC_PER_CLUS_OFFSET_BYTES    13
#define BPB_SEC_PER_FAT_OFFSET_BYTES     19
#define BPB_ROOT_DIR_CLUSTER_OFFSET_BYTES 4

/* This is always the same */
#define BPB_BYTES_PER_SECTOR             512

/* dir entry stuff */
#define DIRENT_LENGTH_BYTES              32
#define DIRENTS_PER_SECTOR               16

#define DIRENT_CLUSTER_HI_OFFSET_BYTES   8
#define DIRENT_CLUSTER_LO_OFFSET_BYTES   4
#define DIRENT_FILENAME_LEN_BYTES        11
#define DIRENT_NAMECHAR_UNUSED           0xE5
#define DIRENT_ATTRIB_DIR                0x10
#define DIRENT_ATTRIB_LFN                0x0F

/* FAT/Cluster chain stuff */
#define EOF_CLUSTER_MARKER               0xFFFFFFFF

#define SHORT_FILENAME_LENGTH_BYTES      13 /* 8 + '.' + 3 + terminating zero */

/* file reading */
/* read a word from disk, and a byte from API, so need
   to do disk read every other byte
*/
#define EVEN_BYTE                        0
#define ODD_BYTE                         1

/* return codes */
#define FAT32_OK                         0
#define FAT32_INVALID_MBR               -10
#define FAT32_PART_NOT_FOUND            -11
#define FAT32_EODIRENTRYS               -12
#define FAT32_DIRENTRY_IS_DIR           -13
#define FAT32_EOF                       -14
#define FAT32_FILE_NOT_FOUND            -15

#define CLUSTERNUMTOLBA(clusternumber)(ClusterBeginLBA + (clusternumber - 2) * SectorsPerCluster)

typedef struct
{
  uint32_t firstcluster;
  uint32_t currentclusternum;
  uint32_t currentsectornum;
  uint32_t currentsectorpos;
  uint32_t sizebytes;
  uint32_t position;
} FD;


int8_t FAT32_Mount(uint8_t drvnum);
int8_t FAT32_DirOpen(const uint8_t *dirname);
int8_t FAT32_DirLoadNextEntry();
uint8_t *FAT32_DirEntryName();

int8_t FAT32_FileOpen(FD *fd, const uint8_t *filename);
int8_t FAT32_FileRead(FD *fd, uint16_t numBytes, uint8_t *dataBuf);

