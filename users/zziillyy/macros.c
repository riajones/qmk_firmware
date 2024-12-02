/* Copyright 2024 Riley Jones <riajones88@gmail.com> @riajones
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


bool handle_key_event(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case ZANE1:
            if (record->event.pressed) {
                send_string("zane1");
            }
            return false;
    }
    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    bool should_propigate = handle_key_event(keycode, record);
    return should_propigate;
}
