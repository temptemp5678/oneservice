<?php
/**
 * @file for Set default title of term
 */

/**
 * Implements custom page redirect, callback from hook_menu()
 */
function othersetting_user_login_link() {
  drupal_goto('user/login');
}
