<?php

function swftools_goswf_admin_form() {

  // Get saved settings
  $saved = _swftools_goswf_settings();

  // See if colorpicker 2 is loaded
  $can_pick = function_exists('colorpicker_2_or_later');

  // Initialise array
  $form = array();

  //Colors
  $form['color'] = array(
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#title' => t('Colors'),
    '#weight' => -1,
  );
  $form['color']['bg'] = array(
	'#type' => ($can_pick ? 'colorpicker_' : '') .'textfield',
	'#size' => 8,
	'#maxlength' => 8,
    '#default_value' => $saved['bg'],
    '#title' => t('Background Color'),
    '#description' => t('Choose a hexadecimal colorcode for the background'),
  );
  $form['color']['nav'] = array(
    '#type' => ($can_pick ? 'colorpicker_' : '') .'textfield',
    '#default_value' => $saved['nav'],
	'#size' => 8,
	'#maxlength' => 8,
    '#title' => t('Navigation Color'),
    '#description' => t('Choose a hexadecimal colorcode for the navigation bar'),
  );

  // Size
  $form['size'] = array(
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#title' => t('Size'),
    '#weight' => 0,
  );
  $form['size']['height'] = array(
    '#type' => 'textfield',
    '#default_value' => $saved['height'],
	'#size' => 8,
    '#title' => t('Height'),
    '#description' => t('The height of the player in pixels.'),
  );
   $form['size']['width'] = array(
    '#type' => 'textfield',
    '#default_value' => $saved['width'],
	'#size' => 8,
    '#title' => t('Width'),
    '#description' => t('The width of the player in pixels.'),
  );

  // Initialise tree as we want to store arrays
  $form['swftools_goswf']['#tree'] = TRUE;

  // Add custom form handler to ensure colors are coded properly
  $form['#submit'][] = 'swftools_goswf_admin_submit';

  // Add custom form handler to flush cache upon submit
  $form['#submit'][] = 'swftools_admin_settings_submit';

  // Return finished form
  return system_settings_form($form);
}

/**
 * Custom form handler to encode colors properly when using color picker module.
 */
function swftools_goswf_admin_submit($form, &$form_state) {

  // Make sure colors are coded properly
  if (function_exists('colorpicker_2_or_later')) {
    foreach (array_keys($form_state['values']) AS $key) {
      $form_state['values'][$key] = preg_replace(array('/^#\s*$/', '/^#/'), array('', '0x'), $form_state['values'][$key]);
    }
  }

}

