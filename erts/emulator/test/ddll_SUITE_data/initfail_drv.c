#include <stdio.h>
#include "erl_driver.h"

static ErlDrvPort erlang_port;
static ErlDrvData easy_start(ErlDrvPort, char*);
static void easy_stop(ErlDrvData), easy_read(ErlDrvData, char*, int);

static ErlDrvEntry easy_driver_entry =
{
  NULL,
  easy_start,
  easy_stop,
  easy_read,
  NULL,
  NULL,
  "easy",
  NULL
};

DRIVER_INIT(initfail_drv)
{
    erlang_port = (ErlDrvPort)-1;
    return 0;
}

static ErlDrvData easy_start(ErlDrvPort port, char *buf)
{
    if (erlang_port != (ErlDrvPort)-1) {
        return ERL_DRV_ERROR_GENERAL;
    }

    fprintf(stderr, "Easy driver started with args %s\n", buf);
    erlang_port = port;
    return (ErlDrvData)port;
}

static void easy_read(ErlDrvData port, char *buf, int count)
{
    driver_output(erlang_port, buf, count);
}

static void easy_stop(ErlDrvData port)
{
    erlang_port = (ErlDrvPort) -1;
}

