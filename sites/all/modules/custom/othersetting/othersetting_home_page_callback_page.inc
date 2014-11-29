<?php
/**
 * @file for Set Home page direct
 */
/**
 * function callback from hook_menu()
 */
function othersetting_home_page_callback() {
  if(user_is_anonymous()) {
    drupal_goto('search-repair');
  }
  else if (user_is_logged_in()) {
    drupal_goto('repair-list');
  }
}