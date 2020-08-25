<?php

namespace App\Controller;

use Symfony\Bundle\FrameworkBundle\Controller\AbstractController;
use Symfony\Component\Routing\Annotation\Route;

class HubController extends AbstractController
{
    /**
     * @Route("/", name="hub")
     */
    public function index()
    {
        return $this->redirectToRoute('app_login');

        return $this->render('hub/index.html.twig', [
            'controller_name' => 'HubController',
        ]);
    }
}
