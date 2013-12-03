<?php
/**
 * Implementation of hook_form()
 *
 * Main config page
 */
function extension_settings_settings($form, &$form_state) {

	$form['extension_settings'] = array(
		'#type' => 'fieldset',
		'#title' => 'Placeholder',
		'#description' => 'Reserving this space for future settings.'
	);
	
	return $form;
}


/*-------------- Top hat settings -------------*/


/**
 * Implementation of hook_form()
 *
 * Top hat config page
 */
function extension_settings_top_hat_settings($form, &$form_state) {
  // Get saved settings
  $settings = variable_get('extension_top_hat_settings', array());

  // Option - Hide utiltity links
  $form['extension_top_hat_options']['hide_utility'] = array(
      '#type'          => 'checkbox',
      '#title'         => 'Hide utitlity links in Top Hat.',
      '#default_value' => isset($settings['hide_utility']) ? $settings['hide_utility'] : 1,
      '#description'   => t('Hide the "Calendar, Library, Maps..." links in the Top Hat'),
      );

  // Option - Display the search form
  $form['extension_top_hat_options']['show_search'] = array(
      '#type'          => 'checkbox',
      '#title'         => 'Show the search form in Top Hat.',
      '#default_value' => isset($settings['show_search']) ? $settings['show_search'] : 0,
      '#description'   => t('Show the search form in the Top Hat:. Requires the OSU Search module.'),
      );

  // Option - VSO Branding
  $form['extension_top_hat_options']['vso_option'] = array(
      '#type'          => 'checkbox',
      '#title'         => 'Use the VSO branding.',
      '#default_value' => isset($settings['vso_option']) ? $settings['vso_option'] : 0,
      '#description'   => t('Set the branding for voluntary organizations. This replaces the tag image with the words Oregon State University.'),
      );

			// Because we have many fields with the same values, we have to set
		  // #tree to be able to access them.
		  $form['#tree'] = TRUE;
		  $form['links_fieldset'] = array(
		    '#type' => 'fieldset',
		    '#title' => t('Top Hat Links'),
		    // Set up the wrapper so that AJAX will be able to replace the fieldset.
		    '#prefix' => '<div id="links-fieldset-wrapper">',
		    '#suffix' => '</div>',
		  );

		  // Build the fieldset with the proper number of links. We'll use
		  // $form_state['num_links'] to determine the number of textfields to build.
		  if (empty($form_state['num_links'])) {
		    $form_state['num_links'] = $settings['num_links'];
		  } 
		  for ($i = 0; $i < $form_state['num_links']; $i++) {
				$form['links_fieldset']['link_fieldset'][$i] = array(
			    '#type' => 'fieldset',
			    '#title' => 'Link ' . ($i+1),
			    // Set up the wrapper so that AJAX will be able to replace the fieldset.
			    '#prefix' => '<div class="link-fieldset-wrapper">',
			    '#suffix' => '</div>',
			  );
			
		    $form['links_fieldset']['link_fieldset'][$i]['title'] = array(
		      '#type' 				 => 'textfield',
					'#default_value' => isset($settings['links']['link_fieldset'][$i]['title']) ? $settings['links']['link_fieldset'][$i]['title'] : '',
		      '#title' 				 => t('Title'),
					'#size'					 => 40,
		    );
		
				$form['links_fieldset']['link_fieldset'][$i]['url'] = array(
		      '#type' 				 => 'textfield',
					'#default_value' => isset($settings['links']['link_fieldset'][$i]['url']) ? $settings['links']['link_fieldset'][$i]['url'] : '',
		      '#title' 				 => t('URL'),
		    );
		
				$form['links_fieldset']['link_fieldset'][$i]['rank'] = array(
		      '#type' 				 => 'textfield',
					'#default_value' => /*isset($settings['links']['link_fieldset'][$i]['weight']) ? $settings['links']['link_fieldset'][$i]['weight'] : 0*/ $i,
		      '#title' 				 => t('Rank'),
					'#size'					 => 5,
		    );
		
				$form['links_fieldset']['link_fieldset'][$i]['delete'] = array(
		      '#type' 				 => 'checkbox',
					'#default_value' => 0,
		      '#title' 				 => t('Delete'),
		    );
	
		  }
		  $form['links_fieldset']['add_link'] = array(
		    '#type' => 'submit',
		    '#value' => t('Add'),
		    '#submit' => array('extension_settings_add_one'),
		    // See the examples in ajax_example.module for more details on the
		    // properties of #ajax.
		    '#ajax' => array(
		      'callback' => 'extension_settings_callback',
		      'wrapper' => 'links-fieldset-wrapper',
		    ),
		  );
		  /*if ($form_state['num_links'] > 1) {
		    $form['links_fieldset']['remove_link'] = array(
		      '#type' => 'submit',
		      '#value' => t('Remove'),
		      '#submit' => array('extension_settings_remove_one'),
		      '#ajax' => array(
		        'callback' => 'extension_settings_callback',
		        'wrapper' => 'links-fieldset-wrapper',
		      ),
		    );
		  }*/
		  $form['submit'] = array(
		    '#type' => 'submit',
		    '#value' => t('Save Settings'),
		  );

  return $form;
}

/**
 * Callback for both ajax-enabled buttons.
 *
 * Selects and returns the fieldset with the names in it.
 */
function extension_settings_callback($form, $form_state) {
  return $form['links_fieldset'];
}

/**
 * Submit handler for the "add-one-more" button.
 *
 * Increments the max counter and causes a rebuild.
 */
function extension_settings_add_one($form, &$form_state) {
  $form_state['num_links']++;
  $form_state['rebuild'] = TRUE;
}

/**
 * Submit handler for the "remove one" button.
 *
 * Decrements the max counter and causes a form rebuild.
 */
/*function extension_settings_remove_one($form, &$form_state) {
  if ($form_state['num_links'] > 1) {
    $form_state['num_links']--;
  }
  $form_state['rebuild'] = TRUE;
}*/

/**
 * Implements hook_form_submit()
 *
 */
function extension_settings_top_hat_settings_submit($form, &$form_state){
  // Create an array of the settings
  $settings = array(
    'hide_utility' => $form_state['values']['extension_top_hat_options']['hide_utility'],
    'show_search'  => $form_state['values']['extension_top_hat_options']['show_search'],
    'vso_option'   => $form_state['values']['extension_top_hat_options']['vso_option'],
		'links'				 => $form_state['values']['links_fieldset'],
		'num_links'		 => $form_state['num_links'],
  );

	// Remove links whose "delete" boxes have been checked
	foreach ($settings['links']['link_fieldset'] as $key => $value) {
		if ($value['delete'] == 1) {
			array_splice($settings['links']['link_fieldset'], $key, 1);
			$settings['num_links']--;
		}
	}
	
	// Sort the links by weight
	function cmp($a, $b){
		return $a['rank']-$b['rank'];
	}
	usort($settings['links']['link_fieldset'], "cmp");
	

  // Save the settings to a variable
  variable_set('extension_top_hat_settings', $settings);

	// Clear the block cache so the changes take effect
	db_query("DELETE FROM cache_block WHERE cache_block.cid LIKE 'extension_settings:extension_top_hat_links%'");
	
  drupal_set_message('The settings have been saved.');

}


/*-------------- Footer settings -------------*/


/**
 * Implementation of hook_form()
 *
 * Footer config page
 */
function extension_settings_footer_settings() {
	
	$settings = variable_get('extension_footer_settings');

	$form['#tree'] = TRUE;
	
  $form['extension_footer_settings']['contact'] = array(
    '#type' => 'textarea',
    '#title' => t('Contact Information'),
    '#default_value' => $settings['contact'],
    '#rows' => '8',
    '#description' => t("HTML markup"),
    '#required' => TRUE,
  );

	$form['extension_footer_settings']['social_media'] = array(
      '#type'  => 'fieldset',
      '#title' => t('Social Media Links'),
      );
  $form['extension_footer_settings']['social_media']['facebook'] = array(
      '#type'          => 'textfield',
      '#title'         => t('Facebook'),
      '#default_value' => isset($settings['social_media']['facebook']) ? $settings['social_media']['facebook'] : '',
      '#size'          => 60,
      '#maxlength'     => 127,
      );
  $form['extension_footer_settings']['social_media']['youtube'] = array(
      '#type'          => 'textfield',
      '#title'         => t('YouTube'),
      '#default_value' => isset($settings['social_media']['youtube']) ? $settings['social_media']['youtube'] : '',
      '#size'          => 60,
      '#maxlength'     => 127,
      );
  $form['extension_footer_settings']['social_media']['flickr'] = array(
      '#type'          => 'textfield',
      '#title'         => t('Flickr'),
      '#default_value' => isset($settings['social_media']['flickr']) ? $settings['social_media']['flickr'] : '',
      '#size'          => 60,
      '#maxlength'     => 127,
      );
  $form['extension_footer_settings']['social_media']['linkedin'] = array(
      '#type'          => 'textfield',
      '#title'         => t('LinkedIn'),
      '#default_value' => isset($settings['social_media']['linkedin']) ? $settings['social_media']['linkedin'] : '',
      '#size'          => 60,
      '#maxlength'     => 127,
      );
  $form['extension_footer_settings']['social_media']['twitter'] = array(
      '#type'          => 'textfield',
      '#title'         => t('Twitter'),
      '#default_value' => isset($settings['social_media']['twitter']) ? $settings['social_media']['twitter'] : '',
      '#size'          => 60,
      '#maxlength'     => 127,
      );
  $form['extension_footer_settings']['social_media']['google'] = array(
      '#type'          => 'textfield',
      '#title'         => t('Google+'),
      '#default_value' => isset($settings['social_media']['google']) ? $settings['social_media']['google'] : '',
      '#size'          => 60,
      '#maxlength'     => 127,
      );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save Settings'),
  );

	return $form;
}

/**
 * Implements hook_form_submit()
 *
 */
function extension_settings_footer_settings_submit($form, &$form_state){

	// Build an array of the settings
	$settings = array(
    'contact' => $form_state['values']['extension_footer_settings']['contact'],
    'social_media'  => $form_state['values']['extension_footer_settings']['social_media'],
  );

	// Save the settings to a variable
  variable_set('extension_footer_settings', $settings);

	// Clear the block caches so the changes take effect
	db_query("DELETE FROM cache_block WHERE cache_block.cid LIKE 'extension_settings:extension_footer%' OR cache_block.cid LIKE 'extension_settings:extension_social_media%'");
	
  drupal_set_message('The settings have been saved.');

}