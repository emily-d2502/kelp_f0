/*
 *      Final 0 - Technion CS 236009 Topics in Linux Kernel Development
 *
 *	Testing - TODO
 *
 *  Authors:
 *          Emily Dror <emily.d@campus.technion.ac.il>
 *          Michael Blum <michael.blum@campus.technion.ac.il>
 */

#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/ioctl.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static const int test_count     = 25;
static const char* dev_path     = "/Users/emilydror/personal/GPU.pdf";
// TODO: "/dev/submarines";

/* ............................ Submarines Definitions ............................ */

#define SUBMARINES_MAGIC            ('s')
#define SUBMARINES_GET_POSITION     _IOR(SUBMARINES_MAGIC, 0x00, int[2])
#define SUBMARINES_RESET            _IO(SUBMARINES_MAGIC, 0x01)
#define SUBMARINES_NEW_LAYOUT       _IOW(SUBMARINES_MAGIC, 0x02, int)
#define SUBMARINES_UNDO             _IO(SUBMARINES_MAGIC, 0x03)

static int submarines_width   = 66;
static int submarines_height  = 20;

static inline int submarines_size(void) {
    return submarines_width * submarines_height;
}
static inline int submarines_index(int row, int col) {
    assert((col < submarines_width) && (row < submarines_height));
    return col + (row * submarines_width);
}

/* ............................ Utilities for TAP testing ............................ */

static int test_current = 1;

static inline void tap_print_header(void) {
    printf("1..%d\n", test_count);
}

static inline int tap_ok(int cond, const char* msg) {
    if (!cond) {
        printf("not ok %d - %s\n", test_current, msg);
        return 1;
    }
    return 0;
}

static inline int tap_test_passed(const char* msg) {
    printf("ok %d - %s passed\n", test_current, msg);
    return 0;
}

static void run_test(int (*test_method)(void)) {
    if (test_method())
        exit(EXIT_FAILURE);

    ++test_current;
}

/* ............................ Tests' Implementation ............................ */

static int test_open(void) {
    int retval = open(dev_path, O_RDWR);
    if (tap_ok(retval != -1, "open valid file path"))
        return 1;

    retval = open("/dev/nonsense", O_RDWR);
    if (tap_ok(retval == -1, "open corrupt file path"))
        return 1;

    return tap_test_passed(__FUNCTION__);
}

static int test_close(void) {
    int retval = open(dev_path, O_RDWR);
    if (tap_ok(retval != -1, "open valid file path"))
        return 1;

    retval = close(retval);
    if (tap_ok(retval != -1, "close file descriptor"))
        return 1;

    return tap_test_passed(__FUNCTION__);
}

static int test_read_simple(void) {
    int fd = open(dev_path, O_RDWR);
    if (tap_ok(fd != -1, "open valid file path"))
        return 1;

    char *buffer = (char *) malloc(submarines_size() * sizeof(char));
	ssize_t bytes_read = read(fd, buffer, submarines_size() * sizeof(char));
    free(buffer);

	if (tap_ok(bytes_read != -1, "read file into large buffer"))
        return 1;


    buffer = (char *) malloc(2 * sizeof(char));
	bytes_read = read(fd, buffer, 2 * sizeof(char));
    free(buffer);

	if (tap_ok(bytes_read != -1, "read file into small buffer"))
        return 1;

    return tap_test_passed(__FUNCTION__);
}

static int test_write_simple(void) {
    // TODO: write into file legal commands

    // TODO: write into file illegal commands

    return tap_test_passed(__FUNCTION__);
}

static int test_read_advanced(void) {
    // TODO: read file into NULL buffer

    // TODO: read file into illegal buffer (OS region)

    return tap_test_passed(__FUNCTION__);
}

static int test_write_advanced(void) {
    // TODO: write into file with NULL buffer

    // TODO: write into file with illegal buffer (OS region)

    return tap_test_passed(__FUNCTION__);
}

static int test_read_initial_board(void) {
    // TODO: verify initial board layout

    return tap_test_passed(__FUNCTION__);
}

static int test_read_middle_game(void) {
    // TODO: read file after write

    // TODO: verify commands behavior

    return tap_test_passed(__FUNCTION__);
}

static int test_write_out_of_bounds(void) {
    // TODO: out of bounds

    return tap_test_passed(__FUNCTION__);
}

static int test_write_whitespaces(void) {
    // TODO: write into file with whitespaces

    return tap_test_passed(__FUNCTION__);
}

static int test_ioctl_simple(void) {
    // TODO: ioctl call with a valid simple request

    // TODO: ioctl call with an invalid request

    return tap_test_passed(__FUNCTION__);
}

static int test_ioctl_get_board(void) {
    // TODO: get board initially

    // TODO: get board after valid move

    // TODO: get board after invalid move

    return tap_test_passed(__FUNCTION__);
}

static int test_ioctl_ask_hints(void) {
    // TODO: ask for hints

    return tap_test_passed(__FUNCTION__);
}

static int test_ioctl_reset_board(void) {
    // TODO: reset board with legal params

    // TODO: reset board with illegal params

    return tap_test_passed(__FUNCTION__);
}

static int test_ioctl_undo_redo(void) {
    // TODO: undo last action

    // TODO: redo last undo

    return tap_test_passed(__FUNCTION__);
}

static int test_lseek_simple(void) {
    // TODO: lseek call with a valid simple request

    // TODO: lseek call with an invalid request

    return tap_test_passed(__FUNCTION__);
}

static int test_lseek_current(void) {
    // TODO: check results of a person's previous actions

    return tap_test_passed(__FUNCTION__);
}

static int test_lseek_start(void) {
    // TODO: check results of a person's previous actions

    return tap_test_passed(__FUNCTION__);
}

static int test_lseek_end(void) {
    // TODO: check results of a person's previous actions

    return tap_test_passed(__FUNCTION__);
}

static int test_lseek_out_of_bounds(void) {
    // TODO: check results of a person's previous actions

    return tap_test_passed(__FUNCTION__);
}

static int test_successful_hit(void) {
    // TODO: check a successful hit

    return tap_test_passed(__FUNCTION__);
}

static int test_successful_miss(void) {
    // TODO: check a successful hit

    return tap_test_passed(__FUNCTION__);
}

static int test_successful_sunk(void) {
    // TODO: check a successful hit

    return tap_test_passed(__FUNCTION__);
}

static int test_successful_victory(void) {
    // TODO: check a successful victory

    return tap_test_passed(__FUNCTION__);
}

static int test_successful_reset(void) {
    // TODO: check a successful reset in the middle of a game

    return tap_test_passed(__FUNCTION__);
}

int main(void) {
    printf("Hello, world!\n");

    run_test(test_open);
    run_test(test_close);

    run_test(test_read_simple);
    run_test(test_write_simple);
    run_test(test_read_advanced);
    run_test(test_write_advanced);

    run_test(test_read_initial_board);
    run_test(test_read_middle_game);
    run_test(test_write_out_of_bounds);
    run_test(test_write_whitespaces);

    run_test(test_ioctl_simple);
    run_test(test_ioctl_get_board);
    run_test(test_ioctl_ask_hints);
    run_test(test_ioctl_reset_board);
    run_test(test_ioctl_undo_redo);

    run_test(test_lseek_simple);
    run_test(test_lseek_current);
    run_test(test_lseek_start);
    run_test(test_lseek_end);
    run_test(test_lseek_out_of_bounds);

    run_test(test_successful_hit);
    run_test(test_successful_miss);
    run_test(test_successful_sunk);
    run_test(test_successful_victory);
    run_test(test_successful_reset);
    return 0;
}
