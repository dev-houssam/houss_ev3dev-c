
/* Author : Houssam BACAR (updated by)
 * ev3_led.h
 * Adaptation de l'API ev3dev-c pour LEGO EV3 sous ev3dev Stretch.
 *
 * Interface conservée à partir de l'en-tête original de
 * Vitaly Kravtsov.
 */

#ifndef EV3_LED_H
#define EV3_LED_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include "ev3.h"

#ifdef EV3_LED_IMPLEMENT

#define EV3_LED_VAR(decl) \
    decl

#define EV3_LED_VAR_INIT(decl, ...) \
    decl = __VA_ARGS__

#define EV3_LED_INL

#else

#define EV3_LED_VAR(decl) \
    extern decl

#define EV3_LED_VAR_INIT(decl, ...) \
    extern decl

#if defined(__GNUC__) && !__GNUC_STDC_INLINE__
#define EV3_LED_INL \
    extern inline
#else
#define EV3_LED_INL \
    inline
#endif

#endif /* EV3_LED_IMPLEMENT */

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Identifiants des LED.
 *
 * Les indices correspondent aux positions des tableaux
 * de chemins définis dans ev3_led.c.
 */
enum {
    EV3_LEFT_GREEN = 0,
    EV3_RIGHT_GREEN,
    EV3_LEFT_RED,
    EV3_RIGHT_RED,

    LED_OUTA,
    LED_OUTB,
    LED_OUTC,
    LED_OUTD,

    LED__COUNT_
};

/*
 * Identifiants des triggers LED.
 */
enum {
    TRIGGER_NONE = 0,
    TRIGGER_MMC0,
    TRIGGER_TIMER,
    TRIGGER_HEARTBEAT,
    TRIGGER_DEFAULT_ON,
    TRIGGER_TRANSIENT,

    TRIGGER_LEGOEV3_BATTERY_CHARGING_OR_FULL,
    TRIGGER_LEGOEV3_BATTERY_CHARGING,
    TRIGGER_LEGOEV3_BATTERY_FULL,
    TRIGGER_LEGOEV3_BATTERY_CHARGING_BLINK_FULL_SOLID,

    TRIGGER_RFKILL0,
    TRIGGER_PHY0RX,
    TRIGGER_PHY0TX,
    TRIGGER_PHY0ASSOC,
    TRIGGER_PHY0RADIO,
    TRIGGER_RFKILL1,

    TRIGGER__COUNT_
};

/*
 * Nombre d'attributs LED gérés par l'API.
 */
#define LED_ATTR__COUNT_ 5

/*
 * Lecture et écriture de la luminosité.
 */
extern size_t get_led_brightness(
    uint8_t inx,
    byte *buf
);

extern size_t set_led_brightness(
    uint8_t inx,
    byte value
);

/*
 * Lecture et écriture du délai d'extinction.
 */
extern size_t get_led_delay_off(
    uint8_t inx,
    int *buf
);

extern size_t set_led_delay_off(
    uint8_t inx,
    int value
);

/*
 * Lecture et écriture du délai d'allumage.
 */
extern size_t get_led_delay_on(
    uint8_t inx,
    int *buf
);

extern size_t set_led_delay_on(
    uint8_t inx,
    int value
);

/*
 * Lecture de la luminosité maximale.
 */
extern size_t get_led_max_brightness(
    uint8_t inx,
    byte *buf
);

/*
 * Lecture et écriture du trigger.
 */
extern size_t get_led_trigger(
    uint8_t inx,
    char *buf,
    size_t sz
);

extern size_t set_led_trigger(
    uint8_t inx,
    char *value
);

/*
 * Récupération de l'indice du trigger actif.
 */
extern INX_T get_led_trigger_inx(
    uint8_t inx
);

/*
 * Modification du trigger à partir de son indice.
 */
extern size_t set_led_trigger_inx(
    uint8_t inx,
    INX_T trigger_inx
);

/*
 * Conversion de l'indice du trigger en chaîne.
 */
extern const char *ev3_led_trigger(
    INX_T trigger_inx
);

#ifdef __cplusplus
}
#endif

#endif /* EV3_LED_H */
