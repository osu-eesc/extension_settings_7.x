<?php
/**
 * @file
 * extension_settings.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function extension_settings_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'extension_settings';
  $context->description = '';
  $context->tag = '';
  $context->conditions = array(
    'path' => array(
      'values' => array(
        '~node/*/edit' => '~node/*/edit',
        '~admin/*' => '~admin/*',
				'~devel/*' => '~devel/*',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'extension_settings-extension_top_hat' => array(
          'module' => 'extension_settings',
          'delta' => 'extension_top_hat',
          'region' => 'top',
          'weight' => '-10',
        ),
        'extension_settings-extension_top_hat_links' => array(
          'module' => 'extension_settings',
          'delta' => 'extension_top_hat_links',
          'region' => 'top',
          'weight' => '-9',
        ),
        'extension_settings-extension_footer' => array(
          'module' => 'extension_settings',
          'delta' => 'extension_footer',
          'region' => 'footer',
          'weight' => '-10',
        ),
        'extension_settings-extension_social_media' => array(
          'module' => 'extension_settings',
          'delta' => 'extension_social_media',
          'region' => 'footer',
          'weight' => '-9',
        ),
      ),
    ),
  );
  $context->condition_mode = 0;
  $export['extension_settings'] = $context;

  return $export;
}
