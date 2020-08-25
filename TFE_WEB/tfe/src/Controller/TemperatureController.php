<?php

namespace App\Controller;

use App\Entity\Temperature;
use Symfony\Bundle\FrameworkBundle\Controller\AbstractController;
use Symfony\Component\Routing\Annotation\Route;

class TemperatureController extends AbstractController
{
    /**
     * @Route("/temperature", name="temperature")
     */
    public function index()
    {
        $temps = $this->getDoctrine()
          ->getRepository(Temperature::class)
          ->findAll();

        return $this->render('temperature/index.html.twig', [
            'controller_name' => 'TemperatureController',
            'temps' => $temps
        ]);
    }
}
