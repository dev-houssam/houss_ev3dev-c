
/* Author : Houssam BACAR
 * ev3_led.c
 * Adaptation des chemins sysfs pour LEGO EV3 sous ev3dev Stretch.
 *
 * Les quatre premières entrées correspondent aux LED de statut
 * de la brique EV3.
 *
 * Les LED des ports A-D ne sont pas configurées ici :
 * leur existence n'a pas été confirmée sur la brique.
 */

#define EV3_LED_IMPLEMENT

#include <string.h>
#include <stdio.h>
#include "ev3.h"
#include "ev3_led.h"

/*
 * Correspondance des LED de statut :
 *
 * LED__LEFT_GREEN  -> led0:green:brick-status
 * LED__RIGHT_GREEN -> led1:green:brick-status
 * LED__LEFT_RED    -> led0:red:brick-status
 * LED__RIGHT_RED   -> led1:red:brick-status
 *
 * Vérifier les quatre noms avec :
 * ls /sys/class/leds/
 */

static const char *const led_attr_brightness[] = {
    "/sys/class/leds/led0:green:brick-status/brightness",
    "/sys/class/leds/led1:green:brick-status/brightness",
    "/sys/class/leds/led0:red:brick-status/brightness",
    "/sys/class/leds/led1:red:brick-status/brightness",
    NULL, /* outA non confirmé */
    NULL, /* outB non confirmé */
    NULL, /* outC non confirmé */
    NULL  /* outD non confirmé */
};

static const char *const led_attr_delay_off[] = {
    "/sys/class/leds/led0:green:brick-status/delay_off",
    "/sys/class/leds/led1:green:brick-status/delay_off",
    "/sys/class/leds/led0:red:brick-status/delay_off",
    "/sys/class/leds/led1:red:brick-status/delay_off",
    NULL,
    NULL,
    NULL,
    NULL
};

static const char *const led_attr_delay_on[] = {
    "/sys/class/leds/led0:green:brick-status/delay_on",
    "/sys/class/leds/led1:green:brick-status/delay_on",
    "/sys/class/leds/led0:red:brick-status/delay_on",
    "/sys/class/leds/led1:red:brick-status/delay_on",
    NULL,
    NULL,
    NULL,
    NULL
};

static const char *const led_attr_max_brightness[] = {
    "/sys/class/leds/led0:green:brick-status/max_brightness",
    "/sys/class/leds/led1:green:brick-status/max_brightness",
    "/sys/class/leds/led0:red:brick-status/max_brightness",
    "/sys/class/leds/led1:red:brick-status/max_brightness",
    NULL,
    NULL,
    NULL,
    NULL
};

static const char *const led_attr_trigger[] = {
    "/sys/class/leds/led0:green:brick-status/trigger",
    "/sys/class/leds/led1:green:brick-status/trigger",
    "/sys/class/leds/led0:red:brick-status/trigger",
    "/sys/class/leds/led1:red:brick-status/trigger",
    NULL,
    NULL,
    NULL,
    NULL
};

/*
 * Vérification commune des indices et des chemins.
 */
static int led_path_valid(uint8_t inx, const char *const paths[])
{
    return inx < LED__COUNT_ && paths[inx] != NULL;
}

size_t get_led_brightness(uint8_t inx, byte *buf)
{
    if (!buf || !led_path_valid(inx, led_attr_brightness))
        return 0;

    return ev3_read_byte(led_attr_brightness[inx], buf);
}

size_t set_led_brightness(uint8_t inx, byte value)
{
    if (!led_path_valid(inx, led_attr_brightness))
        return 0;

    return ev3_write_byte(led_attr_brightness[inx], value);
}

size_t get_led_delay_off(uint8_t inx, int *buf)
{
    if (!buf || !led_path_valid(inx, led_attr_delay_off))
        return 0;

    return ev3_read_int(led_attr_delay_off[inx], buf);
}

size_t set_led_delay_off(uint8_t inx, int value)
{
    if (!led_path_valid(inx, led_attr_delay_off))
        return 0;

    return ev3_write_int(led_attr_delay_off[inx], value);
}

size_t get_led_delay_on(uint8_t inx, int *buf)
{
    if (!buf || !led_path_valid(inx, led_attr_delay_on))
        return 0;

    return ev3_read_int(led_attr_delay_on[inx], buf);
}

size_t set_led_delay_on(uint8_t inx, int value)
{
    if (!led_path_valid(inx, led_attr_delay_on))
        return 0;

    return ev3_write_int(led_attr_delay_on[inx], value);
}

size_t get_led_max_brightness(uint8_t inx, byte *buf)
{
    if (!buf || !led_path_valid(inx, led_attr_max_brightness))
        return 0;

    return ev3_read_byte(led_attr_max_brightness[inx], buf);
}

size_t get_led_trigger(uint8_t inx, char *buf, size_t sz)
{
    if (!buf || sz == 0 ||
        !led_path_valid(inx, led_attr_trigger))
        return 0;

    return ev3_read_char_array(led_attr_trigger[inx], buf, sz);
}

size_t set_led_trigger(uint8_t inx, char *value)
{
    if (!value || !led_path_valid(inx, led_attr_trigger))
        return 0;

    return ev3_write_char_array(led_attr_trigger[inx], value);
}

/*
 * Conversion d'un indice de trigger en nom sysfs.
 */
const char *ev3_led_trigger(INX_T trigger_inx)
{
    switch (trigger_inx) {
    case TRIGGER_NONE:
        return "none";
    case TRIGGER_MMC0:
        return "mmc0";
    case TRIGGER_TIMER:
        return "timer";
    case TRIGGER_HEARTBEAT:
        return "heartbeat";
    case TRIGGER_DEFAULT_ON:
        return "default-on";
    case TRIGGER_TRANSIENT:
        return "transient";
    case TRIGGER_LEGOEV3_BATTERY_CHARGING_OR_FULL:
        return "legoev3-battery-charging-or-full";
    case TRIGGER_LEGOEV3_BATTERY_CHARGING:
        return "legoev3-battery-charging";
    case TRIGGER_LEGOEV3_BATTERY_FULL:
        return "legoev3-battery-full";
    case TRIGGER_LEGOEV3_BATTERY_CHARGING_BLINK_FULL_SOLID:
        return "legoev3-battery-charging-blink-full-solid";
    case TRIGGER_RFKILL0:
        return "rfkill0";
    case TRIGGER_PHY0RX:
        return "phy0rx";
    case TRIGGER_PHY0TX:
        return "phy0tx";
    case TRIGGER_PHY0ASSOC:
        return "phy0assoc";
    case TRIGGER_PHY0RADIO:
        return "phy0radio";
    case TRIGGER_RFKILL1:
        return "rfkill1";
    }

    return STR_unknown_;
}

INX_T get_led_trigger_inx(uint8_t inx)
{
    char buf[256];
    char *p;
    uint8_t trigger_inx = 0;

    if (!get_led_trigger(inx, buf, sizeof(buf)))
        return TRIGGER__COUNT_;

    p = strtok(buf, " ");

    while (p) {
        if (*p == '[')
            return (INX_T)trigger_inx;

        ++trigger_inx;
        p = strtok(NULL, " ");
    }

    return TRIGGER__COUNT_;
}

size_t set_led_trigger_inx(uint8_t inx, INX_T trigger_inx)
{
    const char *trigger = ev3_led_trigger(trigger_inx);

    if (trigger_inx >= TRIGGER__COUNT_ ||
        !led_path_valid(inx, led_attr_trigger))
        return 0;

    return set_led_trigger(inx, (char *)trigger);
}
